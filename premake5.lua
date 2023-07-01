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

project "Mimou"
	kind "SharedLib"
	language "C++"
	location "Mimou"
	cppdialect "C++20"

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
		"%{prj.name}/Vendors/spdlog/include"
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
		"Mimou/Vendors/spdlog/include"
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