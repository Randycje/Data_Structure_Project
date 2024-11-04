#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "json.hpp" // Include this header for JSON handling

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "advapi32.lib")

#define CURL_STATICLIB 
#include <curl/curl.h>

struct HousingRecord {
    std::string month;
    std::string town;
    std::string flatType;
    std::string block;
    std::string streetName;
    std::string storeyRange;
    int floorAreaSqm;

    HousingRecord(const std::string& m, const std::string& t, const std::string& f, const std::string& b,
        const std::string& s, const std::string& sr, const std::string& fa)
        : month(m), town(t), flatType(f), block(b), streetName(s), storeyRange(sr), floorAreaSqm(stoi(fa)) {}
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t newLength = size * nmemb;
    data->append((char*)contents, newLength);
    return newLength;
}

int main() {
    std::string datasetId = "d_8b84c4ee58e3cfc0ece0d773c8ca6abc";
    std::string url = "https://data.gov.sg/api/action/datastore_search?resource_id=" + datasetId;
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            std::vector<HousingRecord> records;

            try {
                auto json = nlohmann::json::parse(readBuffer);
                for (const auto& item : json["result"]["records"]) {
                    records.emplace_back(
                        item.value("month", ""),
                        item.value("town", ""),
                        item.value("flat_type", ""),
                        item.value("block", ""),
                        item.value("street_name", ""),
                        item.value("storey_range", ""),
                        item.value("floor_area_sqm", "0") // Assuming floor_area_sqm might be string
                    );
                }

                for (const auto& rec : records) {
                    std::cout << rec.month << ", " << rec.town << ", " << rec.flatType << ", " << rec.block
                        << ", " << rec.streetName << ", " << rec.storeyRange << ", " << rec.floorAreaSqm << " sqm" << std::endl;
                }
            }
            catch (std::exception& e) {
                std::cerr << "Failed to parse JSON or process it: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
