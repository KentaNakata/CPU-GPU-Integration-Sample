#include "main/main.h"

#include "common/test.h"
#include "cudacommon/test.h"

#include "common/DataContainer.h"
#include "common/DataViewer.h"
#include "cudacommon/compute.h"

void computeSample()
{
    const Point2d<intType>  begin{0, 0};
    const Length2d<intType> size{3, 2};

    DataContainer container(size);
    DataViewer    viewer(container);

    container.value({0, 0}) = 1;
    container.value({2, 1}) = 2;

    viewer.showValues(begin, size);
}

int main()
{
    common::test();
    cudacommon::test();

    std::cout << std::endl;

    computeSample();

    std::cout << std::endl;

    const auto result = cudacommon::compute();
    std::cout << "result: " << result << std::endl;

    return 0;
}
