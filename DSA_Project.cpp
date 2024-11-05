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
#include "Sort.cpp"



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
            HousingList sortedRecords = SortFunction::sortRecords(records);
            sortedRecords.display();
        }

        else if (action == 2) {
            HousingList filteredRecords = filterRecord(records);
            filteredRecords.display();
        }

        else if (action == 3) {
            HousingList searchedRecords = searchRecord(records);
            searchedRecords.display();
    }
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
