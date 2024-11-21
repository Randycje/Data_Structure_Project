#ifndef DSA_PROJECT_H
#define DSA_PROJECT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <functional>

// Represents a single housing record with details such as month, town, type of flat, etc.
struct HousingRecord {
    std::string month;
    std::string town;
    std::string flatType;
    std::string block;
    std::string streetName;
    std::string storeyRange;
    int floorAreaSqm;
    std::string flatModel;
    int leaseCommenceDate;
    std::string remainingLease;
    int resalePrice;

    // Constructor to initialize the HousingRecord with given parameters
    HousingRecord(const std::string& month, const std::string& town, const std::string& flatType,
        const std::string& block, const std::string& streetName, const std::string& storeyRange,
        int floorAreaSqm, const std::string& flatModel, int leaseCommenceDate,
        const std::string& remainingLease, int resalePrice)
        : month(month), town(town), flatType(flatType), block(block), streetName(streetName),
        storeyRange(storeyRange), floorAreaSqm(floorAreaSqm), flatModel(flatModel),
        leaseCommenceDate(leaseCommenceDate), remainingLease(remainingLease), resalePrice(resalePrice) {}

    // Safely converts a string to an integer, returning 0 if conversion fails
    static int safe_parse_int(const std::string& val) {
        try {
            return std::stoi(val);
        }
        catch (const std::exception&) {
            return 0;
        }
    }
};

// Node in a linked list that stores a HousingRecord and a pointer to the next node
struct ListNode {
    HousingRecord data;
    ListNode* next;
    // Constructor that initializes the node with a HousingRecord
    ListNode(const HousingRecord& rec) : data(rec), next(nullptr) {}
};

// Node in a binary tree that stores a HousingRecord and pointers to child nodes
struct TreeNode {
    HousingRecord data;
    TreeNode* left;
    TreeNode* right;

    // Constructor that initializes the tree node with a HousingRecord
    TreeNode(const HousingRecord& rec) : data(rec), left(nullptr), right(nullptr) {}
};

// A singly linked list class to manage a list of HousingRecords
class HousingList {
public:
    ListNode* head; // Points to the first node in the list

    // Constructor initializes the list as empty
    HousingList() : head(nullptr) {}

    // Destructor cleans up all nodes to free memory
    ~HousingList() {
        clear();
    }

    // Appends a new record to the end of the list
    void append(const HousingRecord& rec) {
        if (head == nullptr) {
            head = new ListNode(rec); // If list is empty, create the first node
        }
        else {
            ListNode* current = head; // Start at the head of the list
            while (current->next != nullptr) {
                current = current->next;  // Find the last node
            }
            current->next = new ListNode(rec); // Append new node at the end
        }
    }

    void display() const {
        ListNode* current = head;
        int count = 0;

        // Display the header line
        std::cout << std::setw(7) << "Month" << " | "
            << std::setw(12) << "Town" << " | "
            << std::setw(9) << "FlatType" << " | "
            << std::setw(6) << "Block" << " | "
            << std::setw(20) << "StreetName" << " | "
            << std::setw(15) << "StoreyRange" << " | "
            << std::setw(14) << "FloorAreaSqm" << " | "
            << std::setw(14) << "FlatModel" << " | "
            << std::setw(18) << "LeaseCommenceDate" << " | "
            << std::setw(20) << "RemainingLease" << " | "
            << std::setw(12) << "ResalePrice" << std::endl;

        // Print a separator line to distinguish the headers from the data
        std::cout << std::setw(7) << "-------" << " | "
            << std::setw(12) << "------------" << " | "
            << std::setw(9) << "---------" << " | "
            << std::setw(6) << "------" << " | "
            << std::setw(20) << "--------------------" << " | "
            << std::setw(15) << "---------------" << " | "
            << std::setw(14) << "--------------" << " | "
            << std::setw(14) << "--------------" << " | "
            << std::setw(18) << "------------------" << " | "
            << std::setw(20) << "--------------------" << " | "
            << std::setw(12) << "-----------" << std::endl;

        // Display the data for the first 6 records
        while (current != nullptr && count++ < 6) {
            const auto& rec = current->data;
            std::cout << std::setw(7) << rec.month << " | "
                << std::setw(12) << rec.town << " | "
                << std::setw(9) << rec.flatType << " | "
                << std::setw(6) << rec.block << " | "
                << std::setw(20) << rec.streetName << " | "
                << std::setw(15) << rec.storeyRange << " | "
                << std::setw(14) << rec.floorAreaSqm << " | "
                << std::setw(14) << rec.flatModel << " | "
                << std::setw(18) << rec.leaseCommenceDate << " | "
                << std::setw(20) << rec.remainingLease << " | "
                << std::setw(12) << rec.resalePrice << std::endl;
            current = current->next;
        }
    }

    void clear() {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            temp = nullptr;  // Safeguard against dangling pointers
        }
    }

    void readCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line); // Skip header

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string month, town, flatType, block, streetName, storeyRange, floorAreaSqm, flatModel, leaseCommenceDate, remainingLease, resalePrice;

            std::getline(ss, month, ',');
            std::getline(ss, town, ',');
            std::getline(ss, flatType, ',');
            std::getline(ss, block, ',');
            std::getline(ss, streetName, ',');
            std::getline(ss, storeyRange, ',');
            std::getline(ss, floorAreaSqm, ',');
            std::getline(ss, flatModel, ',');
            std::getline(ss, leaseCommenceDate, ',');
            std::getline(ss, remainingLease, ',');
            std::getline(ss, resalePrice, ',');

            HousingRecord record(month, town, flatType, block, streetName, storeyRange,
                HousingRecord::safe_parse_int(floorAreaSqm), flatModel,
                HousingRecord::safe_parse_int(leaseCommenceDate), remainingLease,
                HousingRecord::safe_parse_int(resalePrice));

            append(record);
        }
        file.close();
    }

    ListNode* mergeSort(ListNode* head, std::function<bool(const HousingRecord&, const HousingRecord&)> compare) {
        if (!head || !head->next) {
            return head; // Base case: if the list is empty or has one node
        }

        ListNode* mid = getMiddleMerge(head);

        ListNode* leftHalf = head;
        ListNode* rightHalf = mid->next;
        mid->next = nullptr; // Detach the right half from the left half


        leftHalf = mergeSort(leftHalf, compare);
        rightHalf = mergeSort(rightHalf, compare);


        ListNode* sorted = merge(leftHalf, rightHalf, compare);
        return sorted;
    }

    ListNode* getMiddleMerge(ListNode* head) { //THIS WORKS DONT TOUCH
        if (!head) return nullptr;  // Early exit if the list is empty.
        ListNode* slow = head;
        ListNode* fast = head->next;  // Start fast one node ahead.

        // Move fast at twice the speed of slow to find the middle node.
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;  // Slow will be at the middle when fast reaches the end.
    }

    ListNode* getMiddle(ListNode* head, ListNode* end) {
        if (!head) return nullptr;  // Early exit if the list is empty.

        ListNode* slow = head;
        ListNode* fast = head->next;

        // Move fast at twice the speed of slow to find the middle node.
        while (fast != end && fast->next != end) {
            slow = slow->next;
            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
            }
        }

        return slow;  // Slow will be at the middle when fast reaches the end.
    }


    // Merge two sorted linked lists
    ListNode* merge(ListNode* left, ListNode* right, std::function<bool(const HousingRecord&, const HousingRecord&)> compare) {
        HousingRecord dummyRecord("Test", "Ang Mo Kio", "2 Room", "100", "Test", "Test", 0, "Test", 0, "Test", 0);

        ListNode dummy(dummyRecord);
        ListNode* current = &dummy;

        while (left && right) {
            if (compare(left->data, right->data)) {
                current->next = left;
                left = left->next;
            }
            else {
                current->next = right;
                right = right->next;
            }
            current = current->next;
        }

        // Attach the remaining elements
        if (left) {
            current->next = left;
        }
        else if (right) {
            current->next = right;
        }

        return dummy.next; // Return the merged list, skipping the dummy node
    }

    // Recursive function to convert sorted linked list to balanced BST
    TreeNode* sortedListToBST(ListNode* start, ListNode* end = nullptr) {
        // Base case: when start is equal to end or start is nullptr, no tree to build
        if (start == nullptr || start == end) {
            return nullptr;
        }

        // Find the middle node
        ListNode* mid = getMiddle(start, end);  // This should properly split the list

        // Create a new TreeNode with the middle node's data
        TreeNode* root = new TreeNode(mid->data);

        // Recursively build left and right subtrees
        root->left = sortedListToBST(start, mid);  // Left subtree (elements before mid)
        root->right = sortedListToBST(mid->next, end);  // Right subtree (elements after mid)

        return root;
    }
};
#endif