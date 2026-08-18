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
    // このCMakeプロジェクト(Main)が依存するプロジェクト(Common)の関数を呼ぶ
    common::test();
    // 外部のCMakeプロジェクト(CudaCommon)をdll経由で呼ぶ
    cudacommon::test();

    std::cout << std::endl;

    computeSample();

    std::cout << std::endl;

    // 外部のCMakeプロジェクト(CudaCommon)のGPUカーネルをdll経由で呼ぶ
    const auto result = cudacommon::compute();
    std::cout << "result: " << result << std::endl;

    return 0;

    // ★★★
    // GPUカーネルを、dllとしてCPUプログラムの外部に切り離すことで、
    // CPU側はicxでビルド・GPU側はmsvcとnvccでビルドなど、コンパイラの使い分け等が可能になる
    // 各環境のビルド設定は、CPU・GPUそれぞれ、CMakePresets.jsonに集約している
}
