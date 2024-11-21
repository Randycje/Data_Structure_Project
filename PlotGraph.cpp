#include "PlotGraph.h"
#include "DSA_Project.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>


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

void PlotGraph::plotResalePricesByFlatType(const HousingList& records) {
    // Step 1: Aggregate resale prices by flat type
    std::map<std::string, std::vector<int>> flatTypePrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        flatTypePrices[current->data.flatType].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each flat type and write to file
    std::ofstream dataFile("plot_data.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data files for plotting." << std::endl;
        return;
    }

    std::map<int, std::string> indexToFlatType;
    int index = 1;
    for (const auto& pair : flatTypePrices) {
        const std::string& flatType = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToFlatType[index] = flatType;  // Store the mapping of index to flat type

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
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Flat Type'\n");
    fprintf(gnuplotPipe, "set xlabel 'Flat Type'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");
    fprintf(gnuplotPipe, "set key outside right top vertical Right noreverse enhanced autotitles columnhead nobox\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToFlatType) {
        if (!first) {
            fprintf(gnuplotPipe, ", ");
        }
        fprintf(gnuplotPipe, "\"%s\" %d", pair.second.c_str(), pair.first);
        first = false;
    }
    fprintf(gnuplotPipe, ")\n");

    // Plot data with boxes and set the xtics
    fprintf(gnuplotPipe, "plot 'plot_data.txt' using 1:2 with boxes fillstyle solid 1.00 border lc rgb 'purple' title 'Average Resale Price'\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void PlotGraph::plotResalePricesByRemainingLease(const HousingList& records) {
    // Step 1: Aggregate resale prices by remaining lease range
    std::map<int, std::vector<int>> leaseRangePrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        int leaseRange = (std::stoi(current->data.remainingLease) / 10) * 10; // Group into 10-year ranges
        leaseRangePrices[leaseRange].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each lease range and write to file
    std::ofstream dataFile("plot_data.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data file for plotting." << std::endl;
        return;
    }

    std::map<int, int> indexToLeaseRange;
    int index = 1;
    for (const auto& pair : leaseRangePrices) {
        int leaseRange = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToLeaseRange[index] = leaseRange;  // Store the mapping of index to lease range

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
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Remaining Lease'\n");
    fprintf(gnuplotPipe, "set xlabel 'Remaining Lease (years)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToLeaseRange) {
        if (!first) {
            fprintf(gnuplotPipe, ", ");
        }
        fprintf(gnuplotPipe, "\"%d-%d\" %d", pair.second, pair.second + 9, pair.first);
        first = false;
    }
    fprintf(gnuplotPipe, ")\n");

    // Plot data with lines and points
    fprintf(gnuplotPipe, "plot 'plot_data.txt' with linespoints title 'Average Resale Price' lc rgb 'purple'\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void PlotGraph::plotResalePricesByFloorArea(const HousingList& records) {
    // Step 1: Aggregate resale prices by floor area range
    std::map<int, std::vector<int>> areaRangePrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        int areaRange = (current->data.floorAreaSqm / 50) * 50; // Group into 50-square meter ranges
        areaRangePrices[areaRange].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each floor area range and write to file
    std::ofstream dataFile("plot_data.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data file for plotting." << std::endl;
        return;
    }

    std::map<int, int> indexToAreaRange;
    int index = 1;
    for (const auto& pair : areaRangePrices) {
        int areaRange = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToAreaRange[index] = areaRange;  // Store the mapping of index to area range

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
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Floor Area'\n");
    fprintf(gnuplotPipe, "set xlabel 'Floor Area (sqm)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");
    fprintf(gnuplotPipe, "set key outside right top vertical Right noreverse enhanced autotitles columnhead nobox\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToAreaRange) {
        if (!first) {
            fprintf(gnuplotPipe, ", ");
        }
        fprintf(gnuplotPipe, "\"%d-%d\" %d", pair.second, pair.second + 49, pair.first);
        first = false;
    }
    fprintf(gnuplotPipe, ")\n");

    // Plot data with boxes and set the xtics
    fprintf(gnuplotPipe, "plot 'plot_data.txt' using 1:2 with boxes fillstyle solid 1.00 border lc rgb 'purple' title 'Average Resale Price'\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void PlotGraph::plotResalePricesByStreetName(const HousingList& records) {
    // Step 1: Aggregate resale prices by street name
    std::map<std::string, std::vector<int>> streetNamePrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        streetNamePrices[current->data.streetName].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each street name and write to file
    std::ofstream dataFile("plot_data.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data file for plotting." << std::endl;
        return;
    }

    std::map<int, std::string> indexToStreetName;
    int index = 1;
    for (const auto& pair : streetNamePrices) {
        const std::string& streetName = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToStreetName[index] = streetName;  // Store the mapping of index to street name

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
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Street Name'\n");
    fprintf(gnuplotPipe, "set xlabel 'Street Name'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToStreetName) {
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

void PlotGraph::plotResalePricesByLeaseCommencementDate(const HousingList& records) {
    // Step 1: Aggregate resale prices by lease commencement date
    std::map<int, std::vector<int>> leaseDatePrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        leaseDatePrices[current->data.leaseCommenceDate].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each lease commencement date and write to file
    std::ofstream dataFile("plot_data.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data file for plotting." << std::endl;
        return;
    }

    std::map<int, int> indexToLeaseDate;
    int index = 1;
    for (const auto& pair : leaseDatePrices) {
        int leaseCommenceDate = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToLeaseDate[index] = leaseCommenceDate;  // Store the mapping of index to lease commence date

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
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Lease Commence Date'\n");
    fprintf(gnuplotPipe, "set xlabe 'Lease Commence Date'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToLeaseDate) {
        if (!first) {
            fprintf(gnuplotPipe, ", ");
        }
        fprintf(gnuplotPipe, "\"%d\" %d", pair.second, pair.first);
        first = false;
    }
    fprintf(gnuplotPipe, ")\n");

    // Plot data with lines and points
    fprintf(gnuplotPipe, "plot 'plot_data.txt' with linespoints title 'Average Resale Price' lc rgb 'purple'\n");

    // Close the pipe
    pclose(gnuplotPipe);
}

void PlotGraph::plotStoreyByResale(const HousingList& records) {
    // Step 1: Aggregate resale prices by storeyRange
    std::map<std::string, std::vector<int>> storeyPrices;
    ListNode* current = records.head;

    while (current != nullptr) {
        storeyPrices[current->data.storeyRange].push_back(current->data.resalePrice);
        current = current->next;
    }

    // Step 2: Calculate average resale price for each storey range and write to file
    std::ofstream dataFile("plot_data.txt");

    if (!dataFile.is_open()) {
        std::cerr << "Error: Could not create data files for plotting." << std::endl;
        return;
    }

    std::map<int, std::string> indexToStoreyRange;
    int index = 1;
    for (const auto& pair : storeyPrices) {
        const std::string& storeyRange = pair.first;
        const std::vector<int>& prices = pair.second;

        // Calculate average resale price
        int sum = 0;
        for (int price : prices) {
            sum += price;
        }
        int averagePrice = sum / prices.size();

        // Write index and average price to data file
        dataFile << index << " " << averagePrice << "\n";
        indexToStoreyRange[index] = storeyRange;  // Store the mapping of index to storey range

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
    fprintf(gnuplotPipe, "set title 'Average Resale Prices by Storey Range'\n");
    fprintf(gnuplotPipe, "set xlabel 'Storey Range'\n");
    fprintf(gnuplotPipe, "set ylabel 'Average Resale Price'\n");

    // Load labels from the file and set them as custom x-axis ticks
    fprintf(gnuplotPipe, "set xtics rotate by -45 font \",8\"\n");
    fprintf(gnuplotPipe, "set xtics (");
    bool first = true;
    for (const auto& pair : indexToStoreyRange) {
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











