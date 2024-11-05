#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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
    std::string flatModel;
    int leaseCommenceDate;
    std::string remainingLease;
    int resalePrice;

    // Constructor that handles JSON parsing with type safety
    HousingRecord(const nlohmann::json& item)
        : month(item.value("month", "")),
        town(item.value("town", "")),
        flatType(item.value("flat_type", "")),
        block(item.value("block", "")),
        streetName(item.value("street_name", "")),
        storeyRange(item.value("storey_range", "")),
        floorAreaSqm(safe_parse_int(item["floor_area_sqm"])),
        flatModel(item.value("flat_model", "")),
        leaseCommenceDate(safe_parse_int(item["lease_commence_date"])),
        remainingLease(item.value("remaining_lease", "")),
        resalePrice(safe_parse_int(item["resale_price"])) {}

    static int safe_parse_int(const nlohmann::json& val) {
        if (val.is_string()) {
            try {
                return std::stoi(val.get<std::string>());
            }
            catch (const std::exception&) {
                return 0;
            }
        }
        else if (val.is_number_integer()) {
            return val.get<int>();
        }
        return 0;
    }
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t newLength = size * nmemb;
    data->append((char*)contents, newLength);
    return newLength;
}

void fetch_data(const std::string& full_url, std::vector<HousingRecord>& records) {
    CURL* curl = curl_easy_init();
    if (curl) {
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            auto json = nlohmann::json::parse(readBuffer);
            for (const auto& item : json["result"]["records"]) {
                records.emplace_back(item);
            }
        }
        else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}

void display_all_records(const std::vector<HousingRecord>& records) {
    std::cout << std::left
        << std::setw(10) << "Month" << std::setw(12) << "Town"
        << std::setw(15) << "Flat Type" << std::setw(6) << "Block"
        << std::setw(20) << "Street Name" << std::setw(15) << "Storey Range"
        << std::setw(14) << "Area (sqm)" << std::setw(15) << "Flat Model"
        << std::setw(12) << "Lease Commence" << std::setw(20) << "Remaining Lease"
        << std::setw(16) << "Resale Price" << std::endl;
    std::cout << std::string(170, '-') << std::endl;

    for (const auto& rec : records) {
        std::cout << std::setw(10) << rec.month
            << std::setw(12) << rec.town
            << std::setw(15) << rec.flatType
            << std::setw(6) << rec.block
            << std::setw(20) << rec.streetName
            << std::setw(15) << rec.storeyRange
            << std::setw(14) << rec.floorAreaSqm
            << std::setw(15) << rec.flatModel
            << std::setw(12) << rec.leaseCommenceDate
            << std::setw(20) << rec.remainingLease
            << std::setw(16) << rec.resalePrice << std::endl;
    }
}

void display_selected_column(const std::vector<HousingRecord>& records, int column) {
    for (const auto& rec : records) {
        switch (column) {
        case 1: std::cout << rec.month << std::endl; break;
        case 2: std::cout << rec.town << std::endl; break;
        case 3: std::cout << rec.flatType << std::endl; break;
        case 4: std::cout << rec.block << std::endl; break;
        case 5: std::cout << rec.streetName << std::endl; break;
        case 6: std::cout << rec.storeyRange << std::endl; break;
        case 7: std::cout << rec.floorAreaSqm << " sqm" << std::endl; break;
        case 8: std::cout << rec.flatModel << std::endl; break;
        case 9: std::cout << rec.leaseCommenceDate << std::endl; break;
        case 10: std::cout << rec.remainingLease << std::endl; break;
        case 11: std::cout << rec.resalePrice << std::endl; break;
        default: std::cout << "Invalid column choice." << std::endl; break;
        }
    }
}

int main() {
    std::vector<HousingRecord> records;
    std::string base_url = "https://data.gov.sg";
    std::string initial_url = "/api/action/datastore_search?resource_id=d_8b84c4ee58e3cfc0ece0d773c8ca6abc&limit=100";
    std::string full_url = base_url + initial_url;
    fetch_data(full_url, records);

    display_all_records(records);

    std::cout << "\nChoose an action:\n1. Sort\n2. Filter\n3. Search\nEnter choice: ";
    int action;
    std::cin >> action;

    std::cout << "Select a column:\n1. Month\n2. Town\n3. Flat Type\n4. Block\n";
    std::cout << "5. Street Name\n6. Storey Range\n7. Floor Area\n";
    std::cout << "8. Flat Model\n9. Lease Commence Date\n10. Remaining Lease\n11. Resale Price\n";
    std::cout << "Enter your choice (1-11): ";
    int column;
    std::cin >> column;

    display_selected_column(records, column);

    // Handle the user's action choice with the appropriate column here
    // This is where you would implement your sorting, filtering, or searching logic based on user input

    return 0;
}