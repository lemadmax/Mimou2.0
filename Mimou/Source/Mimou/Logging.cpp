#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Mimou
{

	std::shared_ptr<spdlog::logger> Logging::EngineLogger;
	std::shared_ptr<spdlog::logger> Logging::ClientLogger;

	void Logging::Init()
	{
		EngineLogger = spdlog::stdout_color_mt("EngineLogger");
		EngineLogger->set_level(spdlog::level::trace);
		ClientLogger = spdlog::stdout_color_mt("ClientLogger");
	}

	inline std::shared_ptr<spdlog::logger> Logging::GetEngineLogger()
	{
		return EngineLogger;
	}

	inline std::shared_ptr<spdlog::logger> Logging::GetClientLogger()
	{
		return ClientLogger;
	}
}