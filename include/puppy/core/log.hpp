/*
 *  log.hpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#ifndef _PUPPY_LOG_HPP
#define _PUPPY_LOG_HPP

#include <memory>
#include "common.hpp"

#define _PUPPY_LOG_CORE_TRACE(...)       ::puppy::log::get_core_logger().trace(std::__VA_ARGS__)
#define _PUPPY_LOG_CORE_DEBUG(...)       ::puppy::log::get_core_logger().debug(__VA_ARGS__)
#define _PUPPY_LOG_CORE_INFO(...)        ::puppy::log::get_core_logger().info(__VA_ARGS__)
#define _PUPPY_LOG_CORE_WARN(...)        ::puppy::log::get_core_logger().warn(__VA_ARGS__)
#define _PUPPY_LOG_CORE_ERROR(...)       ::puppy::log::get_core_logger().error(__VA_ARGS__)
#define _PUPPY_LOG_CORE_CRITICAL(...)    ::puppy::log::get_core_logger().critical(__VA_ARGS__)

#define PUPPY_LOG_TRACE(...)    ::puppy::log::get_client_logger().trace(__VA_ARGS__)
#define PUPPY_LOG_DEBUG(...)    ::puppy::log::get_client_logger().debug(__VA_ARGS__)
#define PUPPY_LOG_INFO(...)     ::puppy::log::get_client_logger().info(__VA_ARGS__)
#define PUPPY_LOG_WARN(...)     ::puppy::log::get_client_logger().warn(__VA_ARGS__)
#define PUPPY_LOG_ERROR(...)    ::puppy::log::get_client_logger().error(__VA_ARGS__)
#define PUPPY_LOG_CRITICAL(...) ::puppy::log::get_client_logger().critical(__VA_ARGS__)

namespace puppy
{
	// ロガークラスの定義
	class PUPPY_EXPORT logger
	{
	public:
		virtual ~logger() = default;

		PUPPY_NON_COPYABLE(logger);
		PUPPY_NON_MOVEABLE(logger);

		virtual void trace(const char* message) const = 0;

		virtual void debug(const char* message) const = 0;

		virtual void info(const char* message) const = 0;

		virtual void warn(const char* message) const = 0;

		virtual void error(const char* message) const = 0;

		virtual void critical(const char* message) const = 0;
	};

	// ログクラスの定義
	class log
	{
	public:
		static const logger& get_core_logger();

		static const logger& get_client_logger();

	private:
		class impl;

		static std::unique_ptr<impl> m_impl;
	};
}

#endif //_PUPPY_LOG_HPP
