/*
 *    ___                        ____                                   __
 *   / _ \__ _____  ___  __ __  / __/______ ___ _  ___ _    _____  ____/ /__
 *  / ___/ // / _ \/ _ \/ // / / _// __/ _ `/  ' \/ -_) |/|/ / _ \/ __/  '_/
 * /_/   \_,_/ .__/ .__/\_, / /_/ /_/  \_,_/_/_/_/\__/|__,__/\___/_/ /_/\_\
 *          /_/  /_/   /___/
 * Copyright (c) 2023 TarobeWanwanLand.
 * Released under the MIT license. see http://opensource.org/licenses/MIT
 */

#ifndef _PUPPY_PLATFORM_HPP
#define _PUPPY_PLATFORM_HPP

// --- プラットフォーム
#define PUPPY_PLATFORM_WINDOWS          0
#define PUPPY_PLATFORM_MACOS            0
#define PUPPY_PLATFORM_LINUX            0
#define PUPPY_PLATFORM_WEB              0

#if defined(_WIN32)
	#if !defined(_WIN64)
		#error Windows x86 is not supported.
	#endif

	#undef  PUPPY_PLATFORM_WINDOWS
	#define PUPPY_PLATFORM_WINDOWS      1
#elif defined(__APPLE__) && defined(__MACH__)
	#undef  PUPPY_PLATFORM_MACOS
	#define PUPPY_PLATFORM_MACOS        1
#elif defined(__linux__)
	#undef  PUPPY_PLATFORM_LINUX
	#define PUPPY_PLATFORM_LINUX        1
#elif defined(__EMSCRIPTEN__)
	#undef  PUPPY_PLATFORM_WEB
	#define PUPPY_PLATFORM_WEB          1
#else
	#error Unsupported platform.
#endif

// --- 命令セット
#define PUPPY_INTRINSIC_SSE             0

#if PUPPY_PLATFORM_WINDOWS
	#undef  PUPPY_INTRINSIC_SSE
	#define PUPPY_INTRINSIC_SSE         1
#elif PUPPY_PLATFORM_MACOS
	#undef  PUPPY_INTRINSIC_SSE
	#define PUPPY_INTRINSIC_SSE         1
#elif PUPPY_PLATFORM_LINUX
	#if defined(__SSE_4_2__) && __SSSE_4_2__
		#undef  PUPPY_INTRINSIC_SSE
		#define PUPPY_INTRINSIC_SSE     1
	#endif
#elif PUPPY_PLATFORM_WEB
	#if defined(__SSE_4_2__) && __SSSE_4_2__
		#undef  PUPPY_INTRINSIC_SSE
		#define PUPPY_INTRINSIC_SSE     1
	#endif
#endif

// --- コンパイラ
#define PUPPY_COMPILER_CLANG            0
#define PUPPY_COMPILER_GCC              0
#define PUPPY_COMPILER_INTEL            0
#define PUPPY_COMPILER_MSVC             0

#if defined(__clang__)
	#undef  PUPPY_COMPILER_CLANG
	#define PUPPY_COMPILER_CLANG        1
#elif defined(__GNUC__)
	#undef  PUPPY_COMPILER_GCC
	#define PUPPY_COMPILER_GCC          1
#elif defined(__INTEL_COMPILER)
	#undef  PUPPY_COMPILER_INTEL
	#define PUPPY_COMPILER_INTEL        1
#elif defined(_MSC_VER)
	#undef  PUPPY_COMPILER_MSVC
	#define PUPPY_COMPILER_MSVC         1
#else
	#error Unsupported compiler.
#endif

// --- ビルドタイプ
#if defined(DEBUG) || defined(_DEBUG)
	#define PUPPY_BUILD_RELEASE         0
	#define PUPPY_BUILD_DEBUG           1
#else
	#define PUPPY_BUILD_RELEASE         1
	#define PUPPY_BUILD_DEBUG           0
#endif

// --- Visibility
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))
	#define PUPPY_VISIBILITY_DEFAULT __attribute__((visibility("default")))
#else
	#define PUPPY_VISIBILITY_HIDDEN
	#define PUPPY_VISIBILITY_DEFAULT
#endif

// --- Force inline
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_FORCE_INLINE __attribute__((always_inline)) inline
#elif PUPPY_COMPILER_MSVC
	#define PUPPY_FORCE_INLINE __forceinline
#else
	#define PUPPY_FORCE_INLINE inline
#endif

// --- コンストラクタでのNodiscard
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_NODISCARD_CTOR [[nodiscard]]
#else
	#define PUPPY_NODISCARD_CTOR
#endif

// --- Likely, Unlikely
 #if (__has_cpp_attribute(likely) >= 201803L)
	#define PUPPY_LIKELY [[likely]]
	#define PUPPY_UNLIKELY [[unlikely]]
#else
	#define PUPPY_LIKELY
	#define PUPPY_UNLIKELY
#endif

// --- Unreachable
#if PUPPY_COMPILER_CLANG && __has_builtin(__builtin_unreachable)
	#define PUPPY_UNREACHABLE __builtin_unreachable();
#elif PUPPY_COMPILER_GCC && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
	#define PUPPY_UNREACHABLE __builtin_unreachable();
#else
	#define PUPPY_UNREACHABLE __assume(0);
#endif

// --- Pretty function
#if PUPPY_COMPILER_CLANG || PUPPY_COMPILER_GCC
	#define PUPPY_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif PUPPY_COMPILER_MSVC
	#define PUPPY_PRETTY_FUNCTION __FUNCSIG__
#elif PPUPPY_COMPILER_INTEL && (__INTEL_COMPILER >= 600)
	#define PUPPY_PRETTY_FUNCTION __FUNCTION__
#else
	#define PUPPY_PRETTY_FUNCTION __func__
#endif

#endif // _PUPPY_PLATFORM_HPP