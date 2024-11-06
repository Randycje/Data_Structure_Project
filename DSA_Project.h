#ifndef DSA_PROJECT_H
#define DSA_PROJECT_H

#include <iostream>
#include <string>
#include <iomanip>
#include "json.hpp" // Include this header for JSON handling (https://github.com/nlohmann/json)

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

    HousingRecord(const std::string& month, const std::string& town, const std::string& flatType,
        const std::string& block, const std::string& streetName, const std::string& storeyRange,
        int floorAreaSqm, const std::string& flatModel, int leaseCommenceDate,
        const std::string& remainingLease, int resalePrice)
        : month(month), town(town), flatType(flatType), block(block), streetName(streetName),
        storeyRange(storeyRange), floorAreaSqm(floorAreaSqm), flatModel(flatModel),
        leaseCommenceDate(leaseCommenceDate), remainingLease(remainingLease), resalePrice(resalePrice) {}

    static int safe_parse_int(const std::string& val) {
        try {
            return std::stoi(val);
        }
        catch (const std::exception&) {
            return 0;
        }
    }
};

struct ListNode {
    HousingRecord data;
    ListNode* next;

    ListNode(const HousingRecord& rec) : data(rec), next(nullptr) {}
};

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class HousingList {
public:
    ListNode* head;

    HousingList() : head(nullptr) {}

    ~HousingList() {
       clear();
    }

    void append(const HousingRecord& rec) {
        if (head == nullptr) {
            head = new ListNode(rec);
        }
        else {
            ListNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new ListNode(rec);
        }
    }

    void display() const {
        ListNode* current = head;
        while (current != nullptr) {
            const auto& rec = current->data;
            std::cout << std::setw(10) << rec.month
                << std::setw(12) << rec.town
                << std::setw(15) << rec.flatType
                << std::setw(6) << rec.block
                << std::setw(20) << rec.streetName
                << std::setw(15) << rec.storeyRange
                << std::setw(14) << rec.floorAreaSqm
                << std::setw(15) << rec.flatModel
                << std::setw(12) << rec.leaseCommenceDate
                << std::setw(20) << rec.remainingLease
                << std::setw(16) << rec.resalePrice << std::endl;
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

        ListNode* mid = getMiddle(head);

        ListNode* leftHalf = head;
        ListNode* rightHalf = mid->next;
        mid->next = nullptr; // Detach the right half from the left half


        leftHalf = mergeSort(leftHalf, compare);
        rightHalf = mergeSort(rightHalf, compare);


        ListNode* sorted = merge(leftHalf, rightHalf, compare);
        return sorted;
    }

    ListNode* getMiddle(ListNode* head) {
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
};
#endif