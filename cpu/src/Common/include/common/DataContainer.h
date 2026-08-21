#pragma once

#include "Accessor.h"

#include <vector>

class Common_API DataContainer {
public:
    using dataType = std::int32_t;

    static inline constexpr MemoryOrder dataOrderType = MemoryOrder::XMajor;

private:
    std::vector<dataType> data;

    const Accessor<dataOrderType> accessor;

public:
    DataContainer(const Length2d<intType>& size, const Point2d<intType> beginPoint = Point2d<intType>{0, 0});

    inline const dataType& value(const Point2d<intType>& p) const { return data[accessor(p)]; }
    inline dataType&       value(const Point2d<intType>& p) { return data[accessor(p)]; }
};
