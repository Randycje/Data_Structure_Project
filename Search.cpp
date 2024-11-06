#include "Search.h"
#include "Sort.h"
#include "DSA_Project.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>

static HousingList searchRecords(HousingList& housingList, int column, const std::string& input) {
    HousingList searchList = housingList;

    // Step 1: Sort the housing list based on the column
    searchList = SortFunction::sortRecords(searchList, column);
    // Step 2: Convert the sorted linked list to a balanced BST
    TreeNode* root = searchList.sortedListToBST(searchList.head);

    // Step 3: Search for all occurrences in the BST
    HousingList resultList;
    SearchFunction::searchInBST(root, input, column, resultList);
    return resultList;
}