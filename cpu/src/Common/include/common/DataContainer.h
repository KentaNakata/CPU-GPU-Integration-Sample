#pragma once

#include "Accessor.h"

#include <vector>

class Common_API DataContainer {
public:
    using vType = std::int32_t;

private:
    std::vector<vType> v;

    const Accessor acc;

public:
    DataContainer(const Length2d<intType>& size);

    inline const vType& value(const Point2d<intType>& p) const { return v[acc(p)]; }
    inline vType&       value(const Point2d<intType>& p) { return v[acc(p)]; }
};
