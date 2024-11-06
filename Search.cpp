#include "Search.h"
#include "Sort.h"
#include "DSA_Project.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

void SearchFunction::searchInBST(TreeNode * root, const std::string & input, int column, HousingList & resultList) {
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

HousingList SearchFunction::searchRecords(HousingList& housingList, int column, const std::string& input) {
    HousingList searchList = housingList;

    //Sort the housing list based on the column
    searchList = SortFunction::sortRecords(searchList, column);
    //Convert the sorted linked list to a balanced BST
    TreeNode* root = searchList.sortedListToBST(searchList.head);

    //Search for all occurrences in the BST
    HousingList resultList;
    SearchFunction::searchInBST(root, input, column, resultList);

    if (resultList.head == nullptr) {
        std::cout << "No matching records found for the input \"" << input << "\" in the selected column.\n" << std::endl;
    }

    return resultList;
}