/*
 *  platform.hpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#ifndef PUPPY_PLATFORM_HPP
#define PUPPY_PLATFORM_HPP

//==================================================
// プラットフォーム
//==================================================
#define PUPPY_TARGET_PLATFORM_PRIVATE_DEFINITION_WINDOWS      0
#define PUPPY_PLATFORM_MACOS        0
#define PUPPY_PLATFORM_LINUX        0

#if defined(_WIN32) || defined(_WIN64)
	#undef PUPPY_PLATFORM_WINDOWS
	#define PUPPY_PLATFORM_WINDOWS  1
	#define PUPPY_PLATFORM_NAME U"Windows"
#elif defined(__APPLE__)
	#undef PUPPY_PLATFORM_MACOS
	#define PUPPY_PLATFORM_MACOS    1
	#define PUPPY_PLATFORM_NAME U"MacOS"
#elif defined(__linux__)
	#undef PUPPY_PLATFORM_LINUX
	#define PUPPY_PLATFORM_LINUX    1
	#define PUPPY_PLATFORM_NAME U"Linux"
#else
	#error "Unsupported platform."
#endif

//==================================================
// コンパイラ
//==================================================
#define PUPPY_COMPILER_CLANG        0
#define PUPPY_COMPILER_GCC          0
#define PUPPY_COMPILER_INTEL        0
#define PUPPY_COMPILER_MSVC         0

#if defined(__clang__)
	#undef PUPPY_COMPILER_CLANG
	#define PUPPY_COMPILER_CLANG    1
	#define PUPPY_COMPILER_NAME U"Clang"
#elif defined(__GNUC__)
	#undef PUPPY_COMPILER_GCC
	#define PUPPY_COMPILER_GCC      1
	#define PUPPY_COMPILER_NAME U"GCC"
#elif defined(__INTEL_COMPILER)
	#undef PUPPY_COMPILER_INTEL
	#define PUPPY_COMPILER_INTEL    1
	#define PUPPY_COMPILER_NAME U"Intel"
#elif defined(_MSC_VER)
	#undef PUPPY_COMPILER_MSVC
	#define PUPPY_COMPILER_MSVC     1
	#define PUPPY_COMPILER_NAME U"MSVC"
#else
	#error "Unsupported compiler."
#endif

//==================================================
// ビルドモード
//==================================================
#if defined(_DEBUG) || defined(DEBUG)
	#define PUPPY_DEBUG 1
#else
	#define PUPPY_DEBUG 0
#endif

//==================================================
// コンパイラ対応
//==================================================

// visibility
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
	#define PUPPY_VISIBILITY_DEFAULT __attribute__((visibility("default")))
#else
	#define PUPPY_VISIBILITY_HIDDEN
	#define PUPPY_VISIBILITY_DEFAULT
#endif

// 強制インライン化
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_FORCE_INLINE __attribute__((always_inline)) inline
#elif PUPPY_COMPILER_MSVC
	#define PUPPY_FORCE_INLINE __forceinline
#else
	#define PUPPY_FORCE_INLINE inline
#endif

// コンストラクタのnodiscard属性
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_NODISCARD_CTOR [[nodiscard]]
#else
	#define PUPPY_NODISCARD_CTOR
#endif

// likely, unlikely
#if (__has_cpp_attribute(likely) >= 201803L)
	#define PUPPY_LIKELY [[likely]]
	#define PUPPY_UNLIKELY [[unlikely]]
#else
	#define PUPPY_LIKELY
	#define PUPPY_UNLIKELY
#endif



#endif //PUPPY_PLATFORM_HPP
