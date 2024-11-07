#include "PlotGraph.h"
#include "DSA_Project.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <string>

// Mock-up function to get attribute value by name
std::string getAttributeValue(const HousingRecord& record, const std::string& attrName) {
    // This should be replaced by actual logic to retrieve attributes by name
    if (attrName == "Month") return record.month;
    if (attrName == "Town") return record.town;
    if (attrName == "FlatType") return record.flatType;
    if (attrName == "Block") return record.block;
    if (attrName == "StreetName") return record.streetName;
    if (attrName == "StoreyRange") return record.storeyRange;
    if (attrName == "FloorAreaSqm") return std::to_string(record.floorAreaSqm);
    if (attrName == "FlatModel") return record.flatModel;
    if (attrName == "LeaseCommenceDate") return std::to_string(record.leaseCommenceDate);
    if (attrName == "RemainingLease") return record.remainingLease;
    if (attrName == "ResalePrice") return std::to_string(record.resalePrice);
    return "";
}

void PlotGraph::generateGraph(const HousingList& list, const std::string& xAttr, const std::string& yAttr, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file '" << filename << "' for writing." << std::endl;
        return;
    }

    file << "digraph HousingList {" << std::endl;
    file << "  rankdir=LR;" << std::endl;
    file << "  node [shape=circle, style=filled, fillcolor=lightgrey, fontcolor=black];" << std::endl;
    file << "  edge [color=red, penwidth=2.0];" << std::endl;

    ListNode* current = list.head;
    int index = 0;
    std::string previousNode;

    while (current != nullptr) {
        std::string xValue = getAttributeValue(current->data, xAttr);
        std::string yValue = getAttributeValue(current->data, yAttr);
        std::string currentNode = "Node" + std::to_string(index);

        file << "  " << currentNode << " [label=\"" << xValue << "\\n" << yValue << "\"];" << std::endl;

        if (!previousNode.empty()) {
            file << "  " << previousNode << " -> " << currentNode << ";" << std::endl;
        }

        previousNode = currentNode;
        current = current->next;
        ++index;
    }

    file << "}" << std::endl;
    file.close();

    std::string cmd = "dot -Tpng " + filename + " -o " + filename + ".png";
    system(cmd.c_str());

    //ListNode* current = list.head;
    //int nodeIndex = 0;
    //while (current != nullptr) {
    //    std::string xValue = getAttributeValue(current->data, xAttr);
    //    std::string yValue = getAttributeValue(current->data, yAttr);
    //    file << "  Node" << nodeIndex << " [label=\"" << xValue << "\\n" << yValue << "\"];" << std::endl;
    //    if (current->next) {
    //        file << "  Node" << nodeIndex << " -> Node" << (nodeIndex + 1) << ";" << std::endl;
    //    }
    //    current = current->next;
    //    ++nodeIndex;
    //}

    //file << "}" << std::endl;
    //file.close();

    //// Optionally, run Graphviz to generate the image
    //std::string cmd = "dot -Tpng " + filename + " -o " + filename + ".png";
    //system(cmd.c_str());
}
