#include <iostream>
#include <string>
#include <iomanip>

#include "DSA_Project.h"
#include "Sort.h"
#include "Search.h"
#include "WriteTOCSV.cpp"


int main() {
    HousingList records;
    std::string filename = "Dataset.csv";
    records.readCSV(filename);
    HousingList backup;
    backup = records;

    int action = 1;

    while (action >= 1 || action <= 5) {
        records.display();

        std::cout << "\nChoose an action:\n1. Sort\n2. Search\n3. Save current list in as csv\n4. Reset Graph\n5. Exit\nEnter choice: ";

        std::cin >> action;

        if (action == 1) {
            std::cout << "\n";
            std::cout << "Select the column to sort by:\n";
            std::cout << "1. Month\n2. Town\n3. Flat Type\n4. Block\n5. Street Name\n6. Storey Range\n7. Floor Area (sqm)\n8. Flat Model\n9. Lease Commencement Date\n10. Remaining Lease\n11. Resale Price\n";
            std::cout << "Enter the number of the column to sort by (1-11): ";
            int choice;
            std::cin >> choice;
            std::cout << "\n";
            records = SortFunction::sortRecords(records, choice);
        }

        else if (action == 2) {
            std::cout << "\n";
            std::cout << "Select the column you want to search by:\n";
            std::cout << "1. Month\n2. Town\n3. Flat Type\n8. Flat Model\n10. Remaining Lease\n11. Resale Price\n";
            std::cout << "Enter the number of the column to search froms: ";
            int choice;
            std::cin >> choice;
            std::cout << "\n";
            std::cout << "Enter the keyword to search (case sensitive): ";
            std::string input;
            std::cin >> std::ws;  // Ignore leading whitespace
            std::getline(std::cin, input);  // Now read the line
            
            //std::cout << "\n";
            HousingList searchedRecords = SearchFunction::searchRecords(records, choice, input); // rmb to implement unique values for user to know what to search for + change resale price to range

            searchedRecords.display();
            
            std::cout << "\nKeep new table? (yes or no): ";
            std::string keep;
            std::cin >> keep;

            if (keep == "yes") {
                records = searchedRecords;
                std::cout << "\n";
            }
            else {
                std::cout << "Nothing done\n";
            }
        }

        else if (action == 3) {
            std::cout << "Save current list as csv? (yes or no)";
            int choice;
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\nSaving...\n";
                WriteToCSV::writeListToCSV(records, "ResaleData.csv");
            }
            else if (choice == 2)  {
                std::cout << "No actions done!\n";
            }
        }

        else if (action == 4) {
            records = backup;
            std::cout << "Dataset has been reverted\n";
        }

        else if (action == 5) {
            std::cout << "Exiting...\n";
            break;
        }
    }
    
    return 0;
}
