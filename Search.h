#ifndef SEARCH_H
#define SEARCH_H

#include "DSA_Project.h"

class SearchFunction {
public:
    // Function to search for multiple occurrences of a value in the BST
    static HousingList searchRecords(HousingList& housingList, int column, const std::string& input);

    static void searchInBST(TreeNode* root, const std::string& input, int column, HousingList& resultList);
};

#endif