#pragma once
#include "Mimou/Logging.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace Mimou
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		// Disallow copying
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& Name, const std::string& FilePath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				if (Logging::GetEngineLogger())
				{
					ME_ENGINE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", Name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(FilePath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new InstrumentationSession({ Name });
				WriteHeader();
			}
			else
			{
				if (Logging::GetEngineLogger())
				{
					ME_ENGINE_ERROR("Instrumentor could not open results file '{0}'.", FilePath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& Result)
		{
			std::stringstream json;
			
			json << std::setprecision(3) << std::fixed;
			json << ", {";
			json << "\"cat\":\" function\",";
			json << "\"dur\":" << (Result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << Result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << Result.ThreadID << ",";
			json << "\"ts\":" << Result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor Instance;
			return Instance;
		}
	private:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{

		}

		~Instrumentor()
		{
			EndSession();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {}, \"traceEvents\": [{}";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		void InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* Name)
			: m_Name(Name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
			{
				Stop();
			}
		}

		void Stop()
		{
			auto EndTimepoint = std::chrono::steady_clock::now();
			auto HighResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto ElapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch() - 
				std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, HighResStart, ElapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils
	{
		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> Result = {};

			size_t SrcIndex = 0;
			size_t DstIndex = 0;
			while (SrcIndex < N)
			{
				size_t MatchIndex = 0;
				while (MatchIndex < K - 1 && SrcIndex + MatchIndex < N - 1 && expr[SrcIndex + MatchIndex] == remove[MatchIndex])
					MatchIndex++;
				if (MatchIndex == K - 1)
					SrcIndex += MatchIndex;
				Result.Data[DstIndex++] = expr[SrcIndex] == '"' ? '\'' : expr[SrcIndex];
				SrcIndex++;
			}
			return Result;
		}
	}
}

#define ME_PROFILE 1
#if ME_PROFILE

#define ME_PROFILE_BEGIN_SESSION(name, filepath) ::Mimou::Instrumentor::Get().BeginSession(name, filepath)
#define ME_PROFILE_END_SESSION() ::Mimou::Instrumentor::Get().EndSession()
// constexpr works the same as const, but allows initialization at compile stage
#define ME_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::Mimou::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											::Mimou::InstrumentationTimer timer##line(fixedName##line.Data)
#define ME_PROFILE_SCOPE_LINE(name, line) ME_PROFILE_SCOPE_LINE2(name, line)
#define ME_PROFILE_SCOPE(name) ME_PROFILE_SCOPE_LINE(name, __LINE__)
#define ME_PROFILE_FUNCTION() ME_PROFILE_SCOPE(__FUNCSIG__)


#else

#define ME_PROFILE_BEGIN_SESSION(name, filepath)
#define ME_PROFILE_END_SESSION()
#define ME_PROFILE_SCOPE(name)
#define ME_PROFILE_FUNCTION()

#endif