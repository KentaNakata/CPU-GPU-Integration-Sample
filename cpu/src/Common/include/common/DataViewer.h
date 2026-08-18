#pragma once

#include "DataContainer.h"

#include <iostream>

class Common_API DataViewer {
    const DataContainer& d;

public:
    DataViewer(const DataContainer& d) : d(d) {}

    void showValues(const Point2d<intType>& start, const Length2d<intType>& count);
};
