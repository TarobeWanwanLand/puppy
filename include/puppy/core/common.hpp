/*
 *    ___                        ____                                   __
 *   / _ \__ _____  ___  __ __  / __/______ ___ _  ___ _    _____  ____/ /__
 *  / ___/ // / _ \/ _ \/ // / / _// __/ _ `/  ' \/ -_) |/|/ / _ \/ __/  '_/
 * /_/   \_,_/ .__/ .__/\_, / /_/ /_/  \_,_/_/_/_/\__/|__,__/\___/_/ /_/\_\
 *          /_/  /_/   /___/
 * Copyright (c) 2023 TarobeWanwanLand.
 * Released under the MIT license. see http://opensource.org/licenses/MIT
 */

#ifndef _PUPPY_COMMON_HPP
#define _PUPPY_COMMON_HPP

#include "export.hpp"
#include "platform.hpp"
#include "types.hpp"

#define PUPPY_TO_STRING(x) _PUPPY_TO_STRING(x)
#define _PUPPY_TO_STRING(x) #x

/// @brief 型のコピーコンストラクタとコピー代入演算子を禁止する
/// @param type_name 型の名前
#define PUPPY_NOT_COPYABLE(type_name)       \
    type_name(type_name const&) = delete;   \
    type_name& operator=(type_name const&) = delete

/// @brief 型のムーブコンストラクタとムーブ代入演算子を禁止する
/// @param type_name 型の名前
#define PUPPY_NOT_MOVEABLE(type_name)       \
    type_name(type_name&&) = delete;        \
    type_name& operator=(type_name&&) = delete

#endif // _PUPPY_COMMON_HPP
