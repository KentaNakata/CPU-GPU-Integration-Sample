#pragma once

#if defined(BUILD_CudaCommon)
#define CudaCommon_API __declspec(dllexport)
#elif defined(USE_CudaCommon)
#define CudaCommon_API __declspec(dllimport)
#else
#define CudaCommon_API
#endif

CudaCommon_API int cudacore();
