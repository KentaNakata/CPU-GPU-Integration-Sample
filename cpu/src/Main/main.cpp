#include "main/main.h"
#include "common/core.h"
#include "cudacommon/cudacore.h"

#include <iostream>

int main()
{
    std::cout << "main/main" << std::endl;
    core();
    cudacore();
    return 0;
}
