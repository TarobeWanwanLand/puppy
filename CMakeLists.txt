cmake_minimum_required(VERSION 3.14)

# プロジェクト定義
project(puppy
	VERSION 0.0.1
	LANGUAGES CXX C
	)

# オプション定義
option(BUILD_SHARED_LIBS "Build shared library" OFF)
option(PUPPY_RTTI_ENABLED "Enable RTTI" OFF)
option(PUPPY_PIC_ENABLED "Enable PIC" ON)
option(PUPPY_BUILD_TESTS "Build puppy tests" OFF)
option(PUPPY_BUILD_EXAMPLES "Build puppy examples" OFF)

# C++20に設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# C17に設定
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# UTF-8を使用する
add_compile_options(-fexec-charset=UTF-8)

# Windowsで共有ライブラリをビルドするために、
# CMAKE_WINDOWS_EXPORT_ALL_SYMBOLSをTRUEに設定
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# PUPPY_PIC_ENABLEDの設定を適用
set(CMAKE_POSITION_INDEPENDENT_CODE ${PUPPY_PIC_ENABLED})

# PUPPY_RTTI_ENABLEDの設定を適用
if (PUPPY_RTTI_ENABLED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")
endif ()

# デバッグビルド時にDEBUGマクロを定義
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# デバッグビルド時のポストフィックスを設定
set(CMAKE_DEBUG_POSTFIX d)

# ヘッダファイル
set(HEADER_FILES
	include/puppy/core/detail/unicode_convert.hpp

	include/puppy/core/assert.hpp
	include/puppy/core/common.hpp
	#include/puppy/core/export.hpp
	include/puppy/core/log.hpp
	include/puppy/core/platform.hpp
	include/puppy/core/string.hpp
	include/puppy/core/types.hpp
	include/puppy/core/utility.hpp
	)

# ライブラリ定義
add_library(puppy)
add_library(puppy::puppy ALIAS puppy)

# ソースファイル
set(SOURCE_FILES
	src/core/log.cpp
	)

# exportヘッダを生成
include(GenerateExportHeader)
generate_export_header(puppy
	EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/puppy/core/export.hpp
	)

# ライブラリにソースを追加
target_sources(puppy
	PRIVATE
	${HEADER_FILES}
	${SOURCE_FILES}
	)

# ソースグループを定義
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

# 外部ライブラリをリンク
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
target_link_libraries(puppy
	PRIVATE
	fmt::fmt
	spdlog::spdlog
	)

# インクルードディレクトリを設定
target_include_directories(puppy
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	)

set(CMAKE_STATIC_LIBRARY_PREFIX)

# ライブラリをインストール
install(TARGETS puppy
	EXPORT puppy-config
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
	)

# インクルードディレクトリをインストール
install(DIRECTORY include DESTINATION include)

# コンフィグをインストール
install(EXPORT puppy-config
	FILE puppy-config.cmake
	NAMESPACE puppy::
	DESTINATION lib/cmake/puppy
	)

# テストのビルド
if (PUPPY_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif ()

# サンプルのビルド
if (PUPPY_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif ()
