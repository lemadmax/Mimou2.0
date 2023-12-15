#pragma once
/*
*	spdlog Wrapper	
*	https://github.com/gabime/spdlog/wiki/1.-QuickStart
*/
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Mimou
{

	class ME_API Logging
	{
	public:
		static void Init();

		static void Uninit();

		static inline Ref<spdlog::logger> GetEngineLogger()
		{
			return EngineLogger;
		}
		static inline Ref<spdlog::logger> GetClientLogger()
		{
			return ClientLogger;
		}

	private:
		static Ref<spdlog::logger> EngineLogger;
		static Ref<spdlog::logger> ClientLogger;
	};

}

#ifndef ME_ENABLE_LOG
//#define ME_ENABLE_LOG 0
#endif

#ifdef ME_ENABLE_LOG | ME_BUILD_DEBUG | ME_BUILD_RELEASE

#define ME_ENGINE_LOG(...) ::Mimou::Logging::GetEngineLogger()->info(__VA_ARGS__)
#define ME_ENGINE_WARN(...) ::Mimou::Logging::GetEngineLogger()->warn(__VA_ARGS__)
#define ME_ENGINE_ERROR(...) ::Mimou::Logging::GetEngineLogger()->error(__VA_ARGS__)
#define ME_ENGINE_TRACE(...) ::Mimou::Logging::GetEngineLogger()->trace(__VA_ARGS__)

#define ME_LOG(...) ::Mimou::Logging::GetClientLogger()->info(__VA_ARGS__)
#define ME_WARN(...) ::Mimou::Logging::GetClientLogger()->warn(__VA_ARGS__)
#define ME_ERROR(...) ::Mimou::Logging::GetClientLogger()->error(__VA_ARGS__)
#define ME_TRACE(...) ::Mimou::Logging::GetClientLogger()->trace(__VA_ARGS__)

#else

#define ME_ENGINE_LOG(...) 
#define ME_ENGINE_WARN(...) 
#define ME_ENGINE_ERROR(...) 
#define ME_ENGINE_TRACE(...) 

#define ME_LOG(...) 
#define ME_WARN(...) 
#define ME_ERROR(...) 
#define ME_TRACE(...) 

#endif