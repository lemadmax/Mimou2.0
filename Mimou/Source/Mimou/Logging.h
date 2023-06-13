#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"

namespace Mimou
{

	class ME_API Logging
	{
	public:
		static void Init();

		static inline std::shared_ptr<spdlog::sinks::wincolor_stdout_sink_mt> GetEngineLogger();
		static inline std::shared_ptr<spdlog::sinks::wincolor_stdout_sink_mt> GetClientLogger();

		static std::shared_ptr<spdlog::sinks::wincolor_stdout_sink_mt> EngineLogger;
		static std::shared_ptr<spdlog::sinks::wincolor_stdout_sink_mt> ClientLogger;
	};

}