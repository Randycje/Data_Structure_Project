#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

#include "DSA_Project.h"
#include "Sort.h"
#include "Search.h"
#include "WriteTOCSV.cpp"
#include "PlotGraph.h"

int main() {
    HousingList records;
    std::string filename = "Dataset-2021.csv";
    records.readCSV(filename);
    HousingList backup;
    backup = records;

    char action = '1';  // Initialize as '1' to enter the loop

    while (true) {
        records.display();

        std::cout << "\nChoose an action:\n1. Sort\n2. Search\n3. Save current list as CSV\n4. Display current list in a Graph\n5. Reset Graph\n6. Exit\nEnter choice: ";
        std::cin >> action;

        // Flush the newline character left in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (action) {
        case '1': {
            std::cout << "\nSelect the column to sort by:\n"
                << "1. Month\n2. Town\n3. Flat Type\n4. Block\n5. Street Name\n6. Storey Range\n"
                << "7. Floor Area (sqm)\n8. Flat Model\n9. Lease Commencement Date\n"
                << "10. Remaining Lease\n11. Resale Price\n"
                << "Enter the number of the column to sort by (1-11): ";
            int choice;
            std::cin >> choice;
            std::cout << "\n";
            records = SortFunction::sortRecords(records, choice);
            break;
        }
        case '2': {
            std::cout << "\nSelect the column you want to search by:\n"
                << "1. Month\n2. Town\n3. Flat Type\n8. Flat Model\n10. Remaining Lease\n11. Resale Price\n"
                << "Enter the number of the column to search from: ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter the keyword to search (case sensitive): ";
            std::string input;
            std::getline(std::cin, input);
            for (char& c : input) {
                c = std::toupper(static_cast<unsigned char>(c)); // Ensure safe conversion to uppercase
            }
            HousingList searchedRecords = SearchFunction::searchRecords(records, choice, input);
            searchedRecords.display();
            std::cout << "\nKeep new table? (yes or no): ";
            std::string keep;
            std::cin >> keep;
            if (keep == "yes") {
                records = searchedRecords;
            }
            else {
                std::cout << "Nothing done\n";
            }
            break;
        }
        case '3': {
            std::cout << "Save current list as CSV? (yes or no):";
            std::string choice;
            std::cin >> choice;
            if (choice == "yes") {
                std::cout << "\nSaving...\n";
                WriteToCSV::writeListToCSV(records, "ResaleData.csv");
            }
            else {
                std::cout << "No actions done!\n";
            }
            break;
        }
        case '4': {
            std::cout << "Display current list in a Graph? (yes or no) *gnuplot must be installed\n";
            std::string choice;
            std::cin >> choice;
            if (choice == "yes") {
                std::cout << "What kind of graph do you want?\n";
                std::cout << "1. Line Graph with Town and Resale\n";
                std::string choice;
                std::cin >> choice;
                if (choice == "1") {
                    std::cout << "Rendering Graph in gnuplot\n";
                    PlotGraph::plotResalePricesByTown(records);
                    std::cout << "Visualising!\n";
                }
            }
            else {
                std::cout << "No actions done!\n";
            }
            break;
        }
        case '5': {
            records = backup;
            std::cout << "Dataset has been reverted\n";
            break;
        }
        case '6': {
            std::cout << "Exiting...\n";
            return 0;
        }
        default:
            std::cout << "Invalid Option. Please choose again.\n";
        }
    }

    return 0;
}
