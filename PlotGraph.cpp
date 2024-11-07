#include "PlotGraph.h"
#include "DSA_Project.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstdio>


#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

void PlotGraph::plotResalePricesByTown(const HousingList& records) {
    // Step 1: Aggregate resale prices by town
    std::map<std::string, std::vector<int>> townPrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        townPrices[current->data.town].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each town and write to file
    std::ofstream dataFile("plot_data.txt");

    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data files for plotting." << std::endl;
        return;
    }

    std::map<int, std::string> indexToTown;
    int index = 1;
    for (const auto& pair : townPrices) {
        const std::string& town = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToTown[index] = town;  // Store the mapping of index to town

        index++;
    }
    dataFile.close();

    // Step 3: Open a pipe to GNUplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error: Could not open pipe to GNUplot." << std::endl;
        return;
    }

    // Step 4: Send commands to GNUplot
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Town'\n");
    fprintf(gnuplotPipe, "set xlabel 'Town'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToTown) {
        if (!first) {
            fprintf(gnuplotPipe, ", ");
        }
        fprintf(gnuplotPipe, "\"%s\" %d", pair.second.c_str(), pair.first);
        first = false;
    }
    fprintf(gnuplotPipe, ")\n");

    // Plot data with lines and points
    fprintf(gnuplotPipe, "plot 'plot_data.txt' with linespoints title 'Average Resale Price' lc rgb 'purple'\n");

    // Close the pipe
    pclose(gnuplotPipe);
}



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