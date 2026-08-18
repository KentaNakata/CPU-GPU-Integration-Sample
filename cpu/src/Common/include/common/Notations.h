#pragma once

#include "api.h"

#include <complex>

using intType     = int;
using realType    = double;
using complexType = std::complex<realType>;

template <typename T>
struct Point2d {
    T x, t;

    Point2d(const T& x, const T& t) : x(x), t(t) {}
};

template <typename T>
struct Length2d {
    T x, t;

    Length2d(const T& x, const T& t) : x(x), t(t) {}
};

template <typename T>
T volume(const Length2d<T>& l)
{
    return l.x * l.t;
}

template <typename T>
Point2d<T> operator+(const Point2d<T>& p1, const Point2d<T>& p2)
{
    return Point2d<T>{p1.x + p2.x, p1.t + p2.t};
}

template <typename T>
Point2d<T> operator+(const Point2d<T>& p1, const Length2d<T>& p2)
{
    return Point2d<T>{p1.x + p2.x, p1.t + p2.t};
}

template <typename T>
Length2d<T> operator-(const Point2d<T>& p1, const Point2d<T>& p2)
{
    return Length2d<T>{p1.x - p2.x, p1.t - p2.t};
}

template <typename T>
struct Point3d {
    T x, y, z;

    Point3d(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
};

template <typename T>
struct Length3d {
    T x, y, z;

    Length3d(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
};

template <typename T>
T volume(const Length3d<T>& l)
{
    return l.x * l.y * l.z;
}

template <typename T>
Point3d<T> operator+(const Point3d<T>& p1, const Point3d<T>& p2)
{
    return Point3d<T>{p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

template <typename T>
Point3d<T> operator+(const Point3d<T>& p1, const Length3d<T>& p2)
{
    return Point3d<T>{p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

template <typename T>
Length3d<T> operator-(const Point3d<T>& p1, const Point3d<T>& p2)
{
    return Length3d<T>{p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}
