#include "Sort.h"
#include <vector>
#include <algorithm>
#include <iostream>


HousingList SortFunction::sortRecords(HousingList& housingList, int choice) {
    // Create a copy of the original list to sort
    HousingList sortedList = housingList; // Make a copy to preserve original list
    std::vector<HousingRecord> records;

    // Sorting based on user choice
    switch (choice) {
    case 1: // Sort by month
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.month < b.month;
            });
        break;
    case 2: // Sort by town
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.town < b.town;
            });
        break;
    case 3: // Sort by flatType
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.flatType < b.flatType;
            });
        break;
    case 4: // Sort by block
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.block < b.block;
            });
        break;
    case 5: // Sort by streetName
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.streetName < b.streetName;
            });
        break;
    case 6: // Sort by storeyRange
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.storeyRange < b.storeyRange;
            });
        break;
    case 7: // Sort by floorAreaSqm
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.floorAreaSqm < b.floorAreaSqm;
            });
        break;
    case 8: // Sort by flatModel
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.flatModel < b.flatModel;
            });
        break;
    case 9: // Sort by leaseCommenceDate
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.leaseCommenceDate < b.leaseCommenceDate;
            });
        break;
    case 10: // Sort by remainingLease
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.remainingLease < b.remainingLease;
            });
        break;
    case 11: // Sort by resalePrice
        sortedList.head = sortedList.mergeSort(sortedList.head, [](const HousingRecord& a, const HousingRecord& b) {
            return a.resalePrice < b.resalePrice;
            });
        break;

    default:
        std::cout << "Invalid choice. Please select a number between 1 and 11." << std::endl;
        return housingList; // Return the original list if choice is invalid
    }

    // Clear the original list and re-populate it with sorted records
    housingList.clear();
    for (const auto& record : records) {
        housingList.append(record);
    }

    std::cout << "Records sorted successfully!\n";
    return housingList; // Return the sorted list
}
