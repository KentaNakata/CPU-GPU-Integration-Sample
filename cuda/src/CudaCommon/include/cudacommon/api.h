#pragma once

// ビルド時はBUILD_CudaCommonマクロを定義。これによりビルド時は、シンボルがエクスポート設定になる
// インストール時はUSE_CudaCommonマクロを定義。これにより外部からdllが参照された時は、シンボルがインポート設定になる

#if defined(BUILD_CudaCommon)
#define CudaCommon_API __declspec(dllexport)
#elif defined(USE_CudaCommon)
#define CudaCommon_API __declspec(dllimport)
#else
#define CudaCommon_API
#endif
