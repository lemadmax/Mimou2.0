#pragma once

#include <memory>

#ifdef ME_PLATFORM_WINDOWS

#ifdef ME_DYNAMIC_LIB

#ifdef ME_BUILD_DLL
#define ME_API __declspec(dllexport)
#else
#define ME_API __declspec(dllimport)
#endif

#else
#define ME_API
#endif

#else
#error Mimou Engine only support Windows at this point

#endif

#ifdef ME_ENABLE_ASSERT
#define ME_ENGINE_ASSERT(x, ...) { if(!(x)) { ME_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#define ME_ASSERT(x, ...) { if(!(x)) { ME_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} } 
#else
#define ME_ENGINE_ASSERT(x, ...)
#define ME_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

namespace Mimou
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&& ...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}