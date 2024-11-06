#include "PlotGraph.h"

namespace plt = matplotlibcpp;

// Function to display available columns
void GraphPlotter::displayColumns(const std::vector<std::vector<std::string>>& columns) const {
    std::cout << "Available columns to plot:" << std::endl;
    for (size_t i = 0; i < columns[0].size(); ++i) {
        std::cout << i + 1 << ". " << columns[0][i] << std::endl;
    }
}

// Function to plot the graph
void GraphPlotter::plotGraph(const std::vector<std::vector<std::string>>& data, const std::vector<std::vector<std::string>>& columns, int xCol, int yCol, int plotType) const
{
    std::vector<double> xData;
    std::vector<double> yData;

    // Extract the selected columns for plotting
    for (const auto& record : data) {
        xData.push_back(std::stod(record[xCol]));
        yData.push_back(std::stod(record[yCol]));
    }

    char title[100];
    std::sprintf(title, "Plot of %s vs %s", columns[0][xCol].c_str(), columns[0][yCol].c_str());

    // Plot the graph based on the selected plot type
    if (plotType == 1) {
        // Line Plot
        plt::plot(xData, yData, "r-");  // Red line
        plt::title(title);
    }
    else if (plotType == 2) {
        // Scatter Plot
        plt::scatter(xData, yData, 10.0);  // Point size of 10
        plt::title(title);
    }
    else if (plotType == 3) {
        // Bar Plot
        plt::bar(xData, yData);
        plt::title(title);

        // Set labels for axes
        plt::xlabel(columns[0][xCol]);
        plt::ylabel(columns[0][yCol]);
        plt::show();
    }
}

// Function to get the user's input for columns and plot type
void GraphPlotter::getUserInput(const std::vector<std::vector<std::string>>& columns,
    const std::vector<std::vector<std::string>>& data) const {
    int xCol, yCol, plotType;

    // Ask user to choose the columns
    std::cout << "Enter the column number for the X axis: ";
    std::cin >> xCol;
    std::cout << "Enter the column number for the Y axis: ";
    std::cin >> yCol;

    // Adjust indices (as users input starts from 1, but vector is 0-indexed)
    --xCol;
    --yCol;

    // Ask for the plot type
    std::cout << "Select the type of graph:" << std::endl;
    std::cout << "1. Line Plot" << std::endl;
    std::cout << "2. Scatter Plot" << std::endl;
    std::cout << "3. Bar Plot" << std::endl;
    std::cout << "Enter the number for the desired plot type: ";
    std::cin >> plotType;

    // Plot the selected graph
    plotGraph(data, columns, xCol, yCol, plotType);
}