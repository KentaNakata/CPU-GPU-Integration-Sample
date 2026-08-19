#pragma once

// ビルド時はBUILD_Commonマクロが定義される。これによりビルド時は、シンボルがエクスポート設定になる
// インストール時はUSE_Commonマクロが定義される。これにより外部からdllが参照された時は、シンボルがインポート設定になる

#if defined(BUILD_Common)
#define Common_API __declspec(dllexport)
#elif defined(USE_Common)
#define Common_API __declspec(dllimport)
#else
#define Common_API
#endif
