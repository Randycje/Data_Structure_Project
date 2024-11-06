#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

class GraphPlotter {
public:
    // Function to display available columns
    void displayColumns(const std::vector<std::vector<std::string>>& columns) const;

    // Function to plot the graph
    void plotGraph(const std::vector<std::vector<std::string>>& data,
        const std::vector<std::vector<std::string>>& columns,
        int xCol, int yCol, int plotType) const;

    // Function to get the user's input for columns and plot type
    void getUserInput(const std::vector<std::vector<std::string>>& columns,
        const std::vector<std::vector<std::string>>& data) const;
};

#endif