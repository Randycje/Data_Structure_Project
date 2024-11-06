#include <iostream>
#include <string>
#include <iomanip>
#include "json.hpp" // Include this header for JSON handling (https://github.com/nlohmann/json)

#define CURL_STATICLIB
#include <curl/curl.h>

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "advapi32.lib")

#include "DSA_Project.h"
#include "Sort.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t newLength = size * nmemb;
    data->append((char*)contents, newLength);
    return newLength;
}

void fetch_data(const std::string& full_url, HousingList& records) {
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
                records.append(HousingRecord(item));
            }
        }
        else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}

int main() {
    HousingList records;
    std::string base_url = "https://data.gov.sg";
    std::string initial_url = "/api/action/datastore_search?resource_id=d_8b84c4ee58e3cfc0ece0d773c8ca6abc&limit=100";
    std::string full_url = base_url + initial_url;
    fetch_data(full_url, records);

    int action = 1;

    while (action != 4) {
        records.display();

        std::cout << "\nChoose an action:\n1. Sort\n2. Filter\n3. Search\n4. Exit\nEnter choice: ";

        std::cin >> action;

        if (action == 1) {
            std::cout << "Select the column to sort by:\n";
            std::cout << "1. Month\n2. Town\n3. Flat Type\n4. Block\n5. Street Name\n6. Storey Range\n7. Floor Area (sqm)\n8. Flat Model\n9. Lease Commencement Date\n10. Remaining Lease\n11. Resale Price\n";
            std::cout << "Enter the number of the column to sort by (1-11): ";
            int choice;
            std::cin >> choice;
            records = SortFunction::sortRecords(records, choice);
           // records.display();
        }

/*        else if (action == 2) {
            HousingList filteredRecords = filterRecord(records);
            filteredRecords.display();
        }

        else if (action == 3) {
            HousingList searchedRecords = searchRecord(records);
            searchedRecords.display();
        }
 */ 
    }
    

    std::cout << "Select a column:\n1. Month\n2. Town\n3. Flat Type\n4. Block\n";
    std::cout << "5. Street Name\n6. Storey Range\n7. Floor Area\n";
    std::cout << "8. Flat Model\n9. Lease Commence Date\n10. Remaining Lease\n11. Resale Price\n";
    std::cout << "Enter your choice (1-11): ";
    int column;
    std::cin >> column;

    records.display_column(column);
    // This part could now include logic to handle sorting, filtering, or searching based on the user's choice

    return 0;
}
