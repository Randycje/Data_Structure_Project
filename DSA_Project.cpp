#include <iostream>
#include <string>
#include "json.hpp" // Include this header for JSON handling

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "advapi32.lib")

#define CURL_STATICLIB 
#include <curl/curl.h>

// Define a node structure for single linked list
struct Node {
    nlohmann::json data;
    Node* next;

    Node(nlohmann::json val) : data(val), next(nullptr) {}
};

// Function to append a new node at the end of the list
void append(Node** head, nlohmann::json value) {
    Node* new_node = new Node(value);
    Node* last = *head;

    if (*head == nullptr) {
        *head = new_node;
        return;
    }

    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = new_node;
}

// This callback function gets called by libcurl as soon as there is data received that needs to be saved.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t newLength = size * nmemb;
    data->append((char*)contents, newLength);
    return newLength;
}

int main() {
    std::string datasetId = "d_8b84c4ee58e3cfc0ece0d773c8ca6abc";
    std::string url = "https://data.gov.sg/api/action/datastore_search?resource_id=" + datasetId;
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            std::cout << "Data retrieved successfully." << std::endl;
            Node* head = nullptr;

            try {
                auto json = nlohmann::json::parse(readBuffer);
                for (auto& item : json["result"]["records"]) {
                    append(&head, item);
                }

                // Printing all the items in the linked list
                Node* temp = head;
                while (temp != nullptr) {
                    std::cout << "Record: " << temp->data.dump() << std::endl;
                    temp = temp->next;
                }
            }
            catch (std::exception& e) {
                std::cerr << "Failed to parse JSON or process it: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}
