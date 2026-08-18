#include "common/DataViewer.h"

void DataViewer::showValues(const Point2d<intType>& start, const Length2d<intType>& count)
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
            std::cout << d.value({x, t}) << "   ";
        }
        std::cout << std::endl;
    }
}
