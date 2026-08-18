#pragma once

#include "Notations.h"

struct Accessor {
    const Length2d<intType> size;

    Accessor(const Length2d<intType>& size) : size(size) {}

    inline intType operator()(const Point2d<intType>& p) const { return p.t * size.t + p.x; }
};
