#include "Search.h"
#include "Sort.h"
#include "DSA_Project.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>


class SearchFunction {
public:
    // Function to search for multiple occurrences of a value in the BST
    static HousingList searchRecords(HousingList& housingList, int column, const std::string& input) {
        HousingList searchList = housingList;

        // Step 1: Sort the housing list based on the column
        searchList = SortFunction::sortRecords(searchList, column);
        // Step 2: Convert the sorted linked list to a balanced BST
        TreeNode* root = searchList.sortedListToBST(searchList.head);

        // Step 3: Search for all occurrences in the BST
        HousingList resultList;
        searchInBST(root, input, column, resultList);
        return resultList;
    }

private:
    // Helper function to search the BST for matching records
    static void searchInBST(TreeNode* root, const std::string& input, int column, HousingList& resultList) {
        if (root == nullptr) {
            return;
        }

        // Determine whether the current node matches the search input based on the column
        bool match = false;
        switch (column) {
        case 1:  // Searching by month
            match = (root->data.month == input);
            break;
        case 2:  // Searching by town
            match = (root->data.town == input);
            break;
        case 3:  // Searching by flatType
            match = (root->data.flatType == input);
            break;
        case 8:  // Searching by flatModel
            match = (root->data.flatModel == input);
            break;
        case 10: // Searching by remainingLease
            match = (root->data.remainingLease == input);
            break;
        case 11: // Searching by resalePrice
            match = (std::to_string(root->data.resalePrice) == input);
            break;
        default:
            std::cout << "Invalid column number." << std::endl;
            return;
        }

        // If a match is found, add the node to the result list
        if (match) {
            resultList.append(root->data);
        }

        // Explore both the left and right subtrees to find duplicates
        if (root->left) {
            searchInBST(root->left, input, column, resultList);  // Continue searching left subtree
        }

        if (root->right) {
            searchInBST(root->right, input, column, resultList);  // Continue searching right subtree
        }
    }
};
//HousingList SearchFunction::searchRecords(HousingList& housingList, int column, std::string input){
//    HousingList searchList = housingList;
//    searchList = SortFunction::sortRecords(searchList, column);
//    TreeNode* root = HousingList::sortedListToBST(searchList.head);
//
//    //1 2 3 8 10 11
//    switch (column) {
//    case 1: // Sort by month
//
//        break;
//    case 2: // Sort by town
//
//        break;
//    case 3: // Sort by flatType
//
//        break;
//    case 4: // Sort by block
//    case 5: // Sort by streetName
//    case 6: // Sort by storeyRange
//    case 7: // Sort by floorAreaSqm
//        break;
//    case 8: // Sort by flatModel
//
//        break;
//    case 9: // Sort by leaseCommenceDate
//        break;
//    case 10: // Sort by remainingLease
//
//        break;
//    case 11: // Sort by resalePrice
//        int minPrice, maxPrice;
//        std::cout << "Please enter your min price: ";
//        std::cin >> minPrice;
//        std::cout << "\nPlease enter your max price: ";
//        std::cin >> maxPrice;
//        std::cout << "\nRange search for resale prices between " << minPrice << " and " << maxPrice << ":" << std::endl;
//        rangeSearch(root, minPrice, maxPrice);
//        break;
//    default:
//        std::cout << "Invalid choice. Please select a number between 1 and 11." << std::endl;
//        return housingList; // Return the original list if choice is invalid
//    }
//
//    std::cout << "Records sorted successfully!\n";
//    return searchList; // Return the sorted list
//}
//
//void rangeSearch(TreeNode* root, int minPrice, int maxPrice) {
//    if (root == nullptr) return;
//
//    // Since it's a BST, we can ignore the left subtree if root's resalePrice is less than minPrice
//    if (root->data.resalePrice > minPrice) {
//        rangeSearch(root->left, minPrice, maxPrice);
//    }
//
//    // Check if the current node's resalePrice falls within the range
//    if (root->data.resalePrice >= minPrice && root->data.resalePrice <= maxPrice) {
//        std::cout << "Resale Price: " << root->data.resalePrice << " | Town: " << root->data.town << std::endl;
//    }
//
//    // Ignore the right subtree if root's resalePrice is greater than maxPrice
//    if (root->data.resalePrice < maxPrice) {
//        rangeSearch(root->right, minPrice, maxPrice);
//    }
//}