#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <string>
#include <ctime>
#include <format>

namespace Mimou
{

	std::shared_ptr<spdlog::logger> Logging::EngineLogger;
	std::shared_ptr<spdlog::logger> Logging::ClientLogger;

	void Logging::Init()
	{
		time_t Now = time(0);
		tm* Ltm = new tm();
		localtime_s(Ltm, &Now);
		std::string LogFileName = std::format("Logs/MELOG_{}_{}_{}_{}_{}.txt", 1900 + Ltm->tm_year, 1 + Ltm->tm_mon, Ltm->tm_mday, Ltm->tm_hour, Ltm->tm_min);
		//spdlog::filename_t = LogFileName;
		
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(LogFileName));
		EngineLogger = std::make_shared<spdlog::logger>("EngineLogger", begin(sinks), end(sinks));
		ClientLogger = std::make_shared<spdlog::logger>("ClientLogger", begin(sinks), end(sinks));

		EngineLogger->info(LogFileName);
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