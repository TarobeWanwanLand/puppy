cmake_minimum_required(VERSION 3.14)

# プロジェクト定義
project(Puppy
	VERSION 0.0.1
	LANGUAGES CXX C)

# オプション定義
option(BUILD_SHARED_LIBS "Build shared library" OFF)
option(PUPPY_BUILD_TESTS "Build Puppy tests" OFF)
option(PUPPY_BUILD_EXAMPLES "Build Puppy examples" OFF)

# C++20に設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# C17に設定
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Windowsで共有ライブラリをビルドするために、
# CMAKE_WINDOWS_EXPORT_ALL_SYMBOLSをTRUEに設定
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# デバッグビルド時のポストフィックスを設定
set(CMAKE_DEBUG_POSTFIX d)

# ライブラリ定義
add_library(Puppy)
add_library(Puppy::Puppy ALIAS Puppy)

# デバッグビルド時にDEBUGマクロを定義
target_compile_definitions(Puppy PUBLIC PUPPY_DEBUG=$<CONFIG:DEBUG>)

# ヘッダファイル
set(HEADER_FILES
	include/puppy/core/common.hpp
	include/puppy/core/contracts.hpp
	include/puppy/core/platform.hpp
	include/puppy/core/string.hpp
	include/puppy/core/string_view.hpp
	include/puppy/core/types.hpp
	)

# ソースファイル
set(SOURCE_FILES
	src/core/string.cpp
	)

# ライブラリにソースを追加
target_sources(Puppy
	PRIVATE
		${HEADER_FILES}
		${SOURCE_FILES})

# ソースグループを定義
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

# 外部ライブラリをリンク
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
target_link_libraries(Puppy
	PRIVATE
	fmt::fmt
	spdlog::spdlog)

# 生成ヘッダのディレクトリ
set(EXPORT_HEADERS_DIR ${CMAKE_BINARY_DIR}/exports)
set(EXPORT_HEADER_FILE export.hpp)

# exportヘッダを生成
include(GenerateExportHeader)
generate_export_header(Puppy
	EXPORT_FILE_NAME "${EXPORT_HEADERS_DIR}/${EXPORT_HEADER_FILE}"
	INCLUDE_GUARD_NAME _PUPPY_EXPORT_HPP)

# インクルードディレクトリを設定
target_include_directories(Puppy
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${EXPORT_HEADERS_DIR}>
	$<INSTALL_INTERFACE:include>)

set(CMAKE_STATIC_LIBRARY_PREFIX)

# ライブラリをインストール
install(TARGETS Puppy
	EXPORT PuppyConfig
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)

# インクルードディレクトリをインストール
install(DIRECTORY include/puppy DESTINATION include)

# 生成したヘッダをすべてインストール
install(FILES "${EXPORT_HEADERS_DIR}/${EXPORT_HEADER_FILE}" DESTINATION include/puppy/core)

# コンフィグをインストール
install(EXPORT PuppyConfig
	FILE PuppyConfig.cmake
	NAMESPACE Puppy::
	DESTINATION lib/cmake/Puppy)

# テストのビルド
if(PUPPY_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

# サンプルのビルド
if(PUPPY_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()
