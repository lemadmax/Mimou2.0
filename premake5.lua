workspace "Mimou2.0"
	configurations {
		"Debug",
		"Release",
		"Dist"
	}
	architecture "x64"
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Mimou/Vendors/GLFW/include"

include "Mimou/Vendors/GLFW"

project "Mimou"
	kind "StaticLib"
	language "C++"
	location "Mimou"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{prj.name}/Binaries/" .. outputdir)
	objdir ("%{prj.name}/Intermediate/" .. outputdir)

	pchheader "mepch.h"
	pchsource "Mimou/Source/mepch.cpp"

	files {
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.c"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/Source",
		"%{prj.name}/Vendors/spdlog/include",
		"%{prj.name}/Vendors/GLM",
		"%{IncludeDir.GLFW}"
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ME_PLATFORM_WINDOWS",
			"ME_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../Sandbox/Binaries/" .. outputdir)
		}

		filter "configurations:Debug"
			defines "ME_BUILD_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "ME_BUILD_RELEASE"
			buildoptions "/MD"
			symbols "on"

		filter "configurations:Dist"
			defines "ME_BUILD_DIST"
			buildoptions "/MD"
			symbols "on"

			
project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	location "Sandbox"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{prj.name}/Binaries/" .. outputdir)
	objdir ("%{prj.name}/Intermediate/" .. outputdir)

	files {
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.c"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/Source",
		"Mimou/Source",
		"Mimou/Vendors/spdlog/include",
		"Mimou/Vendors/GLM"
	}

	links {
		"Mimou"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ME_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "ME_BUILD_DEBUG"
			buildoptions "/MDd"
			symbols "on"

		filter "configurations:Release"
			defines "ME_BUILD_RELEASE"
			buildoptions "/MD"
			symbols "on"

		filter "configurations:Dist"
			defines "ME_BUILD_DIST"
			buildoptions "/MD"
			symbols "on"