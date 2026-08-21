#pragma once

#include "Accessor.h"

#include <vector>

template <typename dataType, MemoryOrder order>
class Common_API DataContainer {
    std::vector<dataType> data;
    const Accessor<order> accessor;

    const Length2d<intType> size;
    const Point2d<intType>  beginPoint;

public:
    DataContainer(const Length2d<intType>& size, const Point2d<intType> beginPoint = Point2d<intType>{0, 0})
        : accessor(size, beginPoint), size(size), beginPoint(beginPoint)
    {
        data.resize(volume(size));
        data.shrink_to_fit();
    }

    inline const dataType& value(const Point2d<intType>& p) const { return data[accessor(p)]; }
    inline dataType&       value(const Point2d<intType>& p) { return data[accessor(p)]; }

    inline Length2d<intType> getSize() const { return size; }
    inline Point2d<intType>  getBeginPoint() const { return beginPoint; }
};
