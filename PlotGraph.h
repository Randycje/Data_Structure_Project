#ifndef PLOTGRAPH_H
#define PLOTGRAPH_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "DSA_Project.h"

class PlotGraph {
public:
    static void plotResalePricesByTown(const HousingList& records);
    static void plotResalePricesByFlatType(const HousingList& records);
    static void plotResalePricesByRemainingLease(const HousingList& records);
    static void plotResalePricesByFloorArea(const HousingList& records);
    static void plotResalePricesByStreetName(const HousingList& records);
    static void plotResalePricesByLeaseCommencementDate(const HousingList& records);
    static void plotStoreyByResale(const HousingList& records);
};
#endif
