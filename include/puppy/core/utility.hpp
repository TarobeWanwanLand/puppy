/*
 *  utility.hpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#ifndef PUPPY_UTILITY_HPP
#define PUPPY_UTILITY_HPP

// クラスのコピーコンストラクタとコピー代入を消すマクロ
#define PUPPY_NOT_COPYABLE(type_name)       \
    type_name(type_name const&) = delete;   \
    type_name& operator=(type_name const&) = delete

// クラスのムーブコンストラクタとムーブ代入を消すマクロ
#define PUPPY_NOT_MOVEABLE(type_name)       \
    type_name(type_name&&) = delete;        \
    type_name& operator=(type_name&&) = delete

#endif //PUPPY_UTILITY_HPP
