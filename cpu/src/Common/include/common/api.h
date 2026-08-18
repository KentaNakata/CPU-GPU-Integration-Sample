#pragma once

// ビルド時はBUILD_Commonマクロを定義。これによりビルド時は、シンボルがエクスポート設定になる
// インストール時はUSE_Commonマクロを定義。これにより外部からdllが参照された時は、シンボルがインポート設定になる

#if defined(BUILD_Common)
#define Common_API __declspec(dllexport)
#elif defined(USE_Common)
#define Common_API __declspec(dllimport)
#else
#define Common_API
#endif
