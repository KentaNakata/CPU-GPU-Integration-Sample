#pragma once

#include "notations.h"

enum class MemoryOrder { XMajor, TMajor };

template <MemoryOrder order>
struct Accessor {
    const intType          Nx;
    const intType          Nt;
    const Point2d<intType> beginPoint;
    const intType          reducedBeginPoint;

    Accessor(const Length2d<intType>& size, const Point2d<intType> beginPoint = Point2d<intType>{0, 0})
        : Nx(size.x), Nt(size.t), beginPoint(beginPoint), reducedBeginPoint(reduce(beginPoint))
    {
    }

    inline intType reduce(const Point2d<intType>& p) const
    {
        // ゼロコスト抽象化のために、constexpr if を使う
        if constexpr (order == MemoryOrder::XMajor) {
            return p.t * Nx + p.x;
        }
        if constexpr (order == MemoryOrder::TMajor) {
            return p.x * Nt + p.t;
        }
    };

    inline intType convertToIndex(const Point2d<intType>& p) const { return reduce(p) - reducedBeginPoint; };

    // DataContainer クラスの保持する std::vector data のインデックスを返す
    inline intType operator()(const Point2d<intType>& p) const { return convertToIndex(p); }

    inline void incrementX(intType& p) const
    {
        if constexpr (order == MemoryOrder::XMajor) {
            p += 1;
        }
        if constexpr (order == MemoryOrder::TMajor) {
            p += Nt;
        }
    }
    inline void incrementT(intType& p) const
    {
        if constexpr (order == MemoryOrder::XMajor) {
            p += Nx;
        }
        if constexpr (order == MemoryOrder::TMajor) {
            p += 1;
        }
    }
    inline void decrementX(intType& p) const
    {
        if constexpr (order == MemoryOrder::XMajor) {
            p -= 1;
        }
        if constexpr (order == MemoryOrder::TMajor) {
            p -= Nt;
        }
    }
    inline void decrementT(intType& p) const
    {
        if constexpr (order == MemoryOrder::XMajor) {
            p -= Nx;
        }
        if constexpr (order == MemoryOrder::TMajor) {
            p -= 1;
        }
    }
};
