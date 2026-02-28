#include "main/main.h"
#include "common/test.h"
#include "cudacommon/test.h"

int main()
{
    common_test();
    cudacommon_test();
    return 0;
}
