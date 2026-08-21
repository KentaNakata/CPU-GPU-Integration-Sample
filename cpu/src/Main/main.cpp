#include "common/test.h"
#include "cudacommon/test.h"

#include "common/compute.h"
#include "cudacommon/compute.h"

#include <iostream>

int main()
{
    // 外部のCMakeプロジェクトの関数をDLL/SO経由で呼ぶ
    common::test();
    cudacommon::test();

    std::cout << std::endl;
    std::cout << "compute with CPU" << std::endl;

    common::compute();

    std::cout << std::endl;
    std::cout << "compute with GPU" << std::endl;

    const auto result = cudacommon::compute();
    std::cout << "result: " << result << std::endl;

    return 0;

    // ★★★
    // GPUカーネルを、dllとしてCPUプログラムの外部に切り離すことで、
    // CPU側はicxでビルド・GPU側はmsvcとnvccでビルドなど、コンパイラの使い分け等が可能になる
    // 各環境のビルド設定は、CPU・GPUそれぞれ、CMakePresets.jsonに集約している
}
