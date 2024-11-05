#include <iostream>
#include <string>
#include <vector>
#include "json.hpp" // Include this header for JSON handling (https://github.com/nlohmann/json)

#define CURL_STATICLIB
#include <curl/curl.h>

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "advapi32.lib")

struct HousingRecord {
    std::string month;
    std::string town;
    std::string flatType;
    std::string block;
    std::string streetName;
    std::string storeyRange;
    int floorAreaSqm;

    // Constructor that handles JSON parsing with type safety
    HousingRecord(const nlohmann::json& item) {
        month = item.value("month", "");
        town = item.value("town", "");
        flatType = item.value("flat_type", "");
        block = item.value("block", "");
        streetName = item.value("street_name", "");
        storeyRange = item.value("storey_range", "");

        std::string areaStr = item.value("floor_area_sqm", "0"); // Default to "0" if not found
        // Convert string to integer safely
        floorAreaSqm = try_parse_int(areaStr);
    }

    static int try_parse_int(const std::string& str) {
        try {
            return std::stoi(str);
        }
        catch (const std::exception&) {
            return 0; // Return 0 or a default value if parsing fails
        }
    }
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t newLength = size * nmemb;
    data->append((char*)contents, newLength);
    return newLength;
}

void fetch_data(const std::string& full_url, std::vector<HousingRecord>& records, int currentPage, int maxPages) {
    if (currentPage > maxPages) return; // Stop fetching when the page limit is reached

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            try {
                auto json = nlohmann::json::parse(readBuffer);
                for (const auto& item : json["result"]["records"]) {
                    records.emplace_back(item);
                }

                // Check if there's a "next" link and recurse
                if (!json["result"]["_links"]["next"].is_null() && currentPage < maxPages) {
                    std::string next_url = "https://data.gov.sg" + json["result"]["_links"]["next"].get<std::string>();
                    fetch_data(next_url, records, currentPage + 1, maxPages);
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Failed to parse JSON or process it: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}

int main() {
    std::vector<HousingRecord> records;
    std::string base_url = "https://data.gov.sg";
    std::string initial_url = "/api/action/datastore_search?resource_id=d_8b84c4ee58e3cfc0ece0d773c8ca6abc&limit=100";
    std::string full_url = base_url + initial_url;
    fetch_data(full_url, records, 1, 10); // Fetch only the first 10 pages

    for (const auto& rec : records) {
        std::cout << rec.month << ", " << rec.town << ", " << rec.flatType << ", " << rec.block
            << ", " << rec.streetName << ", " << rec.storeyRange << ", " << rec.floorAreaSqm << " sqm" << std::endl;
    }

    return 0;
}
