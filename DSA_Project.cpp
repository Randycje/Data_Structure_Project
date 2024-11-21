#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <algorithm>

#include "DSA_Project.h"
#include "Sort.h"
#include "Search.h"
#include "WriteTOCSV.cpp"
#include "PlotGraph.h"

int main() {
    HousingList records; // Initialize a HousingList object to store housing records
    std::string filename = "Dataset.csv"; // Specify the filename of the CSV file containing the housing data
    records.readCSV(filename); // reading the excel file, and populates `records` with the data
    HousingList backup = records;  // Backup to revert any changes

    std::string input;
    while (true) { // infinite loop to keep the program running till the user exits
        records.display(); // displaying the record

        std::cout << "\nChoose an action:\n1. Sort\n2. Search\n3. Save current list as CSV\n4. Display current list in a Graph\n5. Reset Graph\n6. Exit\nEnter choice: ";
        std::getline(std::cin, input);

        int action = 0;
        std::stringstream actionStream(input);  
        // Input Validation
        if (!(actionStream >> action) || !actionStream.eof() || action < 1 || action > 6) {
            std::cout << "Invalid option. Please enter a number from 1 to 6.\n";
            continue;
        }

        switch (action) {
        // Sorting function
        case 1: {
            std::string input;
            int choice;
            while (true) {
                std::cout << "\nSelect the column to sort by:\n"
                    << "1. Month\n2. Town\n3. Flat Type\n4. Block\n5. Street Name\n6. Storey Range\n"
                    << "7. Floor Area (sqm)\n8. Flat Model\n9. Lease Commencement Date\n"
                    << "10. Remaining Lease\n11. Resale Price\n12. Go Back\n"
                    << "Enter the number of the column to sort by (1-12): ";
                std::getline(std::cin, input);
                std::stringstream choiceStream(input);
                if (choiceStream >> choice && choiceStream.eof() && choice >= 1 && choice <= 12) {
                    break; // Valid input
                }
                std::cout << "Invalid input, please try again using numbers 1 to 12.\n";
            }
            if (choice == 12) {
                std::cout << "Returning to main menu...\n";
                break;
            }
            records = SortFunction::sortRecords(records, choice);
            break;
        }

        // Searching function
        case 2: {
            std::string input;
            int choice;
            while (true) {
                std::cout << "\nSelect the column you want to search by:\n"
                    << "1. Month\n2. Town\n3. Flat Type\n8. Flat Model\n10. Remaining Lease\n11. Resale Price\n12. Go Back\n"
                    << "Enter the number of the column to search from (1-12): ";
                std::getline(std::cin, input);
                std::stringstream choiceStream(input);
                if (!(choiceStream >> choice) || !choiceStream.eof()) {
                    std::cout << "Invalid input, please try again.\n";
                    continue;
                }
                // Validate if the choice is one of the explicitly allowed options
                if (choice == 1 || choice == 2 || choice == 3 || choice == 8 || choice == 10 || choice == 11 || choice == 12) {
                    break; // Valid input
                }
                else {
                    std::cout << "Invalid choice, please select a valid column number or '12' to go back.\n";
                }
            }
            if (choice == 12) {
                std::cout << "Returning to main menu...\n";
                break;
            }

            std::cout << "Enter the keyword to search: ";
            std::string keyword;
            std::getline(std::cin, keyword);
            for (char& c : keyword) {
                c = std::toupper(static_cast<unsigned char>(c)); // Convert input to uppercase
            }
            HousingList searchedRecords = SearchFunction::searchRecords(records, choice, keyword);
            searchedRecords.display();
            std::cout << "\nKeep new table? (yes or no): ";
            while (true) {
                std::getline(std::cin, input);
                if (input == "yes" || input == "no") {
                    break;  // Valid input
                }
                std::cout << "Invalid response. Please enter 'yes' or 'no': ";
            }

            if (input == "yes") {
                records = searchedRecords;
            }
            else {
                std::cout << "Nothing done, returning to main menu.\n";
            }
            break;
        }
        // Exporting as CSV function
        case 3: {
            std::string choice;
            while (true) {
                std::cout << "Save current list as CSV? (yes or no): ";
                std::getline(std::cin, choice);
                if (choice == "yes" || choice == "no" || choice == "back") {
                    break;
                }
                else {
                    std::cout << "Invalid input, please enter 'yes', 'no', or 'back' to return to the main menu.\n";
                }
            }
            if (choice == "yes") {
                std::cout << "\nSaving...\n";
                WriteToCSV::writeListToCSV(records, "ResaleData.csv");
                std::cout << "Data saved successfully to 'ResaleData.csv'.\n";
            }
            else if (choice == "back") {
                std::cout << "Returning to main menu...\n";
                break;
            }
            else {
                std::cout << "No actions done!\n";
            }
            break;
        }
        // Displaying Graph in Gnuplot function
        case 4: {
            std::string choice;
            while (true) {
                std::cout << "What kind of graph do you want?\n"
                    << "1. Line Graph with Town and Resale\n2. Bar Graph with Flat Type and Resale\n"
                    << "3. Line Graph with Remaining Lease and Resale\n4. Bar Graph with Floor Area and Resale\n"
                    << "5. Line Graph with Street Name and Resale\n6. Line Graph with Lease Commencement and Resale\n"
                    << "7. Line Graph with Storey Range and Resale\n"
                    << "8. Go Back\n"
                    << "Enter your choice (1-8): ";
                std::getline(std::cin, choice);
                std::stringstream graphStream(choice);
                int graphChoice;
                if (graphStream >> graphChoice && graphStream.eof()) {
                    if (graphChoice >= 1 && graphChoice <= 8) {
                        break; // Valid input
                    }
                }
                std::cout << "Invalid choice, please select a number from 1 to 8.\n";
            }
            if (stoi(choice) == 8) {
                std::cout << "Returning to previous menu...\n";
                break; // Exit the switch without plotting any graph
            }
            std::cout << "Rendering Graph in gnuplot\n";
            switch (stoi(choice)) {
            case 1:
                PlotGraph::plotResalePricesByTown(records);
                break;
            case 2:
                PlotGraph::plotResalePricesByFlatType(records);
                break;
            case 3:
                PlotGraph::plotResalePricesByRemainingLease(records);
                break;
            case 4:
                PlotGraph::plotResalePricesByFloorArea(records);
                break;
            case 5:
                PlotGraph::plotResalePricesByStreetName(records);
                break;
            case 6:
                PlotGraph::plotResalePricesByLeaseCommencementDate(records);
                break;
            case 7:
                PlotGraph::plotStoreyByResale(records);
                break;
            default:
                std::cout << "Invalid choice. No graph will be displayed.\n";
            }
            std::cout << "Visualising!\n";
            break;
        }
        // Resetting list function
        case 5: {
            std::string confirmation;
            while (true) {
                std::cout << "Are you sure you want to revert to the original dataset? This action cannot be undone.\n";
                std::cout << "Type 'yes' to confirm or 'no' to cancel: ";
                std::getline(std::cin, confirmation);
                // Convert the user input to lowercase for consistent comparison (optional)
                std::transform(confirmation.begin(), confirmation.end(), confirmation.begin(),
                    [](unsigned char c) { return std::tolower(c); });

                if (confirmation == "yes") {
                    records = backup; // Revert the dataset to the backup
                    std::cout << "Dataset has been reverted to the original state.\n";
                    break; // Break the loop after action confirmed
                }
                else if (confirmation == "no") {
                    std::cout << "Revert cancelled. Returning to main menu.\n";
                    break; // Break the loop after cancelation
                }
                else {
                    std::cout << "Invalid input. Please type 'yes' to confirm or 'no' to cancel.\n"; // Reprompt if input is invalid
                }
            }
            break;
        }
        // Exiting the program
        case 6:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid Option. Please choose again.\n";
        }
    }
    return 0;
}
