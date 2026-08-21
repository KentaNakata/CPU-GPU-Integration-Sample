#include "common/DataContainer.h"

DataContainer::DataContainer(const Length2d<intType>& size, const Point2d<intType> beginPoint)
    : accessor(size, beginPoint)
{
    data.resize(volume(size));
    data.shrink_to_fit();
}