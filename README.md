# CPU/GPU サンプルプロジェクト

## はじめに

このプロジェクトは、CPU と GPU(CUDA) を組み合わせた C++ ベースのサンプルプログラムです。

**ポイント**：GPU側の計算を、DLL/SOとしてCPUプログラムの外部に切り離しています。これにより、

> CPU側はicxでビルド・GPU側はmsvcとnvccでビルド

など、コンパイラの細かい使い分け等が可能になります。
環境ごとに個別のビルド設定は、CPU・GPUそれぞれ、CMakePresets.jsonに集約しています。サーバーごとに設定の異なる項目はここで吸収します。

※ このREADMEはAIによる要約を含みます。

## 📝 プログラムの概要

### 主な機能
- **CPU 側**: 2次元データコンテナの管理、データビューアーでの表示
- **GPU 側**: 簡単な CUDA カーネルの呼び出し

### 技術スタック
- **言語**: C++20, CUDA
- **ビルドシステム**: CMake
- **コンパイラ**: MSVC, NVCC 等

---

## 📁 プロジェクト構成

```
dlybbs/
├── README.md                  # このファイル
├── .clang-format              # コード整形設定
├── .gitignore                 # Git 無視ファイル
│
├── cpu/                       # CPU コンポーネント
│   ├── CMakeLists.txt
│   ├── CMakePresets.json
│   └── src/
│       ├── Common/            # 共有ライブラリ (Core, Test)
│       │   ├── CMakeLists.txt
│       │   ├── compute.cpp
│       │   ├── DataContainer.cpp
│       │   ├── DataViewer.cpp
│       │   ├── test.cpp
│       │   ├── include/
│       │   │   └── common/
│       │   │       ├── Accessor.h        # メモリアクセス補助
│       │   │       ├── api.h             # DLL インポート/エクスポート マクロ
│       │   │       ├── compute.h
│       │   │       ├── DataContainer.h   # データコンテナクラス
│       │   │       ├── DataViewer.h      # データ表示クラス
│       │   │       ├── notations.h       # 2D/3D 型定義
│       │   │       └── test.h
│       │   └── cmake/
│       │       └── CommonConfig.cmake
│       │
│       └── Main/              # メイン実行ファイル
│           ├── CMakeLists.txt
│           └── main.cpp
│
└── cuda/                      # CUDA コンポーネント
    ├── CMakeLists.txt
    ├── CMakePresets.json
    └── src/
        └── CudaCommon/        # CUDA ライブラリ (CudaCore, CudaTest)
            ├── CMakeLists.txt
            ├── compute.cu     # CUDA カーネル実装
            ├── test.cpp
            ├── include/
            │   └── cudacommon/
            │       ├── api.h              # DLL エクスポート マクロ
            │       ├── compute.h          # 計算関数の宣言
            │       └── test.h
            └── cmake/
                └── CudaCommonConfig.cmake
```

### ディレクトリの役割

| ディレクトリ | 説明 |
|------------|------|
| `cpu/` | CPU コンポーネントのルート。Common ライブラリと Main 実行ファイルを含む |
| `cuda/` | CUDA コンポーネントのルート。GPU 計算用ライブラリを含む |
| `src/Common/` | CPU 用の共有ライブラリ（データコンテナ、ビューアー） |
| `src/Main/` | CPU コンポーネントのメインプログラム |
| `src/CudaCommon/` | CUDA 計算ライブラリ（GPU カーネル実装） |
| `include/` | ヘッダーファイル（public インターフェース） |
| `cmake/` | CMake 設定ファイル |

---

## ⚙️ CMakePresets.json の説明

`CMakePresets.json` は、CMake のビルド設定を定義するファイルです。複数のプリセットが用意されており、各プリセットで異なるビルド環境を構成します。

### プリセット一覧

#### 基本プリセット（継承用）

| プリセット | 説明 |
|-----------|------|
| `default` | デフォルト設定。出力ディレクトリ、キャッシュ変数を定義 |
| `debug` | Debug ビルド用（CMAKE_BUILD_TYPE=Debug） |
| `release` | Release ビルド用（CMAKE_BUILD_TYPE=Release） |
| `local` | ローカル開発環境用（Ninja ジェネレータ、MSVC コンパイラ） |

#### 実行可能なプリセット

| プリセット | 概要 |
|-----------|------|
| `local-debug` | ローカル開発環境での Debug ビルド |
| `local-release` | ローカル開発環境での Release ビルド |

### 出力ディレクトリ

ビルド後、以下の構造が生成されます：

```
out/
├── build/
│   ├── local-debug/      # Debug ビルドのオブジェクトファイル
│   └── local-release/    # Release ビルドのオブジェクトファイル
└── install/
    ├── local-debug/      # Debug インストール先
    └── local-release/    # Release インストール先
```

---

## 🔨 ビルド方法

### 前提条件

下記環境でビルドを確認しました。

- Visual Studio 2026 (MSVC 14.51)
- Ninja 1.13.2
- NVIDIA GPU Computing Toolkit CUDA 13.3

### 1. CUDA コンポーネントのビルド

```bash
cd cuda
cmake --preset local-release
cmake --build --preset local-release
cmake --install --prefix out/install/local-release
```

**出力**: `cuda/out/install/local-release/` に DLL/SO ファイルがインストールされます

### 2. CPU コンポーネントのビルド

```bash
cd cpu
cmake --preset local-release
cmake --build --preset local-release
cmake --install --prefix out/install/local-release
```

**出力**: `cpu/out/install/local-release/bin/Main.exe` に実行ファイルが生成されます

### 3. 実行ファイルの実行

```bash
# CPU ビルドディレクトリへ移動
cd cpu/out/build/local-release

# 実行
./bin/Main.exe
```

### Debug ビルドの場合

プリセット名を `local-debug` に変更してください：

```bash
cd cuda
cmake --preset local-debug
cmake --build --preset local-debug
```

---

## 📊 プログラムの実行フロー

```
Main.exe
├─ common::test()         → "Hello from Common" を出力
├─ cudacommon::test()     → "Hello from CudaCommon" を出力
├─ computeSample()        → データコンテナの操作デモ
│  ├─ DataContainer を生成
│  ├─ データを設定
│  └─ DataViewer で表示
└─ cudacommon::compute()  → CUDA カーネルを実行、結果を返す
   ├─ GPU メモリ確保
   ├─ カーネル実行 (<<<1,1>>>)
   └─ 結果をホストメモリにコピー
```

### 実行時の出力例

```
Hello from Common
Hello from CudaCommon

     x=0 x=1 x=2 
t=0:   1   0   0   
t=1:   0   0   2   

Hello from kernel()
result: 9
```

---

## 🛠️ トラブルシューティング

### CUDACommon が見つからないエラー

```
CMake Error: Could not find CudaCommon
```

**解決策**: CUDA をまず先にビルドしてください
```bash
cd cuda
cmake --preset local-release
cmake --build --preset local-release
```

### Ninja が見つからないエラー

```bash
# Ninja をインストール
choco install ninja      # Windows (Chocolatey)
sudo apt install ninja-build  # Ubuntu/Debian
brew install ninja       # macOS
```

---
