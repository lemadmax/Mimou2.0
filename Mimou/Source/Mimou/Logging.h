#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Mimou
{

	class ME_API Logging
	{
	public:
		static void Init();

		static inline std::shared_ptr<spdlog::logger> GetEngineLogger();
		static inline std::shared_ptr<spdlog::logger> GetClientLogger();

		static std::shared_ptr<spdlog::logger> EngineLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};

}