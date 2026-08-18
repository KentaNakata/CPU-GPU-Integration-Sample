#pragma once

#if defined(BUILD_Common)
#define Common_API __declspec(dllexport)
#elif defined(USE_Common)
#define Common_API __declspec(dllimport)
#else
#define Common_API
#endif
