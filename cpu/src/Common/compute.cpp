#include "common/compute.h"

#include "common/DataContainer.h"
#include "common/DataViewer.h"

namespace common {

int compute()
{
    // データ型とメモリ連続方向の指定
    using dataType                 = intType;
    constexpr auto memoryOrderType = MemoryOrder::XMajor;

    // データサイズと始点の指定
    const Length2d<intType> size{3, 2};
    const Point2d<intType>  begin{0, 0};

    // データコンテナとデータビューワーの作成
    DataContainer<dataType, memoryOrderType> container(size, begin);
    DataViewer                               viewer(container);

    // 適当な計算
    container.value({0, 0}) = 1;
    container.value({1, 0}) = 1;
    container.value({2, 0}) = 1;
    container.value({1, 1}) = container.value({0, 0}) + container.value({1, 0}) + container.value({2, 0});

    // 結果の表示
    viewer.showAllValues();

    return 0;
}

}    // namespace common
