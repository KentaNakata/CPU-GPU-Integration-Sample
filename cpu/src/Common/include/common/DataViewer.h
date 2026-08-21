#pragma once

#include "DataContainer.h"

#include <iostream>

template <typename dataType, MemoryOrder order>
class Common_API DataViewer {
    const DataContainer<dataType, order>& container;

public:
    DataViewer(const DataContainer<dataType, order>& container) : container(container) {}

    void showAllValues() const { showValues(container.getBeginPoint(), container.getSize()); }

    void showValues(const Point2d<intType>& start, const Length2d<intType>& count) const
    {
        const auto end = start + count;

        std::cout << "     ";
        for (intType x = start.x; x < end.x; ++x) {
            std::cout << "x=" << x << " ";
        }
        std::cout << std::endl;

        for (intType t = start.t; t < end.t; ++t) {
            std::cout << "t=" << t << ":   ";
            for (intType x = start.x; x < end.x; ++x) {
                std::cout << container.value({x, t}) << "   ";
            }
            std::cout << std::endl;
        }
    }
};
