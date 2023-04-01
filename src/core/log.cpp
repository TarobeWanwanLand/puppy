/*
 *  log.cpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#include "puppy/core/log.hpp"
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace puppy
{
	class spdlog_logger final : public logger
	{
	public:
		explicit spdlog_logger(std::shared_ptr<spdlog::logger>&& logger) noexcept
			: m_logger(std::move(logger))
		{
		}

		~spdlog_logger() = default;

		void trace   (const char* msg) const override { m_logger->trace(msg); }
		void debug   (const char* msg) const override { m_logger->debug(msg); }
		void info    (const char* msg) const override { m_logger->info(msg); }
		void warn    (const char* msg) const override { m_logger->warn(msg); }
		void error   (const char* msg) const override { m_logger->error(msg); }
		void critical(const char* msg) const override { m_logger->critical(msg); }

	private:
		std::shared_ptr<spdlog::logger> m_logger;
	};

	class log::impl
	{
	public:
		impl()
		{
			constexpr const char* pattern = "[%Y-%m-%d %H:%M:%S.%e] [%-5n] [%^%=8l%$] [thread %t] %v";

			// エラーハンドラを設定
			spdlog::set_error_handler([](const std::string& msg) { std::cerr << msg << std::endl; });

			// ローテーションファイルシンクを作成
			auto rotating_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("puppy.log", 1024 * 1024 * 5, 3);
			rotating_file_sink->set_pattern(pattern);

			// 標準出力シンクを作成
			auto stdout_color_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			stdout_color_sink->set_pattern(pattern);

			// シンクをリスト化
			const auto sink_list = std::vector<spdlog::sink_ptr>{ rotating_file_sink, stdout_color_sink };

			// コアロガーを作成
			auto core_spdlog_logger = std::make_shared<spdlog::logger>("PUPPY", sink_list.begin(), sink_list.end());
			core_spdlog_logger->set_level(spdlog::level::trace);
			core_spdlog_logger->flush_on(spdlog::level::trace);
			m_core_logger = std::make_unique<spdlog_logger>(std::move(core_spdlog_logger));

			// クライアントロガーを作成
			auto client_spdlog_logger = std::make_shared<spdlog::logger>("APP", sink_list.begin(), sink_list.end());
			client_spdlog_logger->set_level(spdlog::level::trace);
			client_spdlog_logger->flush_on(spdlog::level::trace);
			m_client_logger = std::make_unique<spdlog_logger>(std::move(client_spdlog_logger));
		}

		~impl()
		{
			// ロガーを破棄
			spdlog::drop_all();
		}

		std::unique_ptr<spdlog_logger> m_core_logger;
		std::unique_ptr<spdlog_logger> m_client_logger;
	};

	std::unique_ptr<log::impl> log::m_impl = std::make_unique<log::impl>();

	const logger& log::get_core_logger()
	{
		return *m_impl->m_core_logger;
	}

	const logger& log::get_client_logger()
	{
		return *m_impl->m_client_logger;
	}
}
