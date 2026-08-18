#include "common/DataContainer.h"

DataContainer::DataContainer(const Length2d<intType>& size) : acc(size)
{
    v.resize(volume(size));
    v.shrink_to_fit();
}