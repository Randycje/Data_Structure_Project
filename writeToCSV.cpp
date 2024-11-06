#include <fstream>
#include <sstream>
#include <iostream>
#include "DSA_Project.h"

class WriteToCSV {
public:
    // Public method to write the HousingList data to a CSV file
    static void writeListToCSV(const HousingList& housingList, const std::string& filename) {
        // Open a file for writing
        std::ofstream file(filename);

        // Check if the file is open
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        // Write the header line (column names)
        file << "Month,Town,FlatType,Block,StreetName,StoreyRange,FloorAreaSqm,FlatModel,LeaseCommenceDate,RemainingLease,ResalePrice" << std::endl;

        // Write the data from the list
        ListNode* current = housingList.head;
        while (current != nullptr) {
            const HousingRecord& record = current->data;

            // Write the record data as CSV (comma-separated)
            file << record.month << ","
                << record.town << ","
                << record.flatType << ","
                << record.block << ","
                << record.streetName << ","
                << record.storeyRange << ","
                << record.floorAreaSqm << ","
                << record.flatModel << ","
                << record.leaseCommenceDate << ","
                << record.remainingLease << ","
                << record.resalePrice << std::endl;

            current = current->next;
        }

        // Close the file after writing
        file.close();
        std::cout << "Data successfully written to " << filename << std::endl;
    }
};