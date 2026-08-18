#include "main/main.h"
#include "common/test.h"
#include "cudacommon/test.h"

#include "common/DataContainer.h"
#include "common/DataViewer.h"

int main()
{
    common_test();
    cudacommon_test();

    std::cout << std::endl;

    DataContainer d({3, 2});
    DataViewer    v(d);

    d.value({1, 1}) = 1;
    v.showValues({0, 0}, {3, 2});

    return 0;
}
