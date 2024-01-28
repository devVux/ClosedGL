#pragma once

#include "spdlog/spdlog.h"
#include <memory>


class Log {

	public:

		static void init();

		inline static std::shared_ptr<spdlog::logger>& coreLogger() { return sCoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& clientLogger() { return sClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;

};


// Core log macros
#define FATAL(...)	Log::coreLogger()->fatal(__VA_ARGS__)
#define ERRORE(...)	Log::coreLogger()->error(__VA_ARGS__)
#define WARN(...)	Log::coreLogger()->warn(__VA_ARGS__)
#define INFO(...)	Log::coreLogger()->info(__VA_ARGS__)
#define TRACE(...)	Log::coreLogger()->trace(__VA_ARGS__)
