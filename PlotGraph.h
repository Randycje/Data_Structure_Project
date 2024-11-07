#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DSA_Project.h"

class PlotGraph {
public:
    static void generateGraph(const HousingList& list, const std::string& xAttr, const std::string& yAttr, const std::string& filenam);
};
#endif
