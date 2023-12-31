workspace "Mimou2.0"
	configurations {
		"DevEditor",
		"Debug",
		"Release",
		"Dist"
	}
	architecture "x64"
	startproject "MimouEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "Mimou/Vendors/Glad/include"
IncludeDir["GLFW"] = "Mimou/Vendors/GLFW/include"
IncludeDir["ImGUI"] = "Mimou/Vendors/ImGUI"
IncludeDir["stb_image"] = "Mimou/Vendors/stb_image"
IncludeDir["EnTT"] = "Mimou/Vendors/EnTT/single_include"
IncludeDir["YAML"] = "Mimou/Vendors/yaml-cpp/include"

include "Mimou/Vendors/Glad"
include "Mimou/Vendors/GLFW"
include "Mimou/Vendors/ImGUI"
include "Mimou/Vendors/yaml-cpp"

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
		"%{prj.name}/Source/**.c",
		"%{prj.name}/Vendors/stb_image/**.h",
		"%{prj.name}/Vendors/stb_image/**.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/Source",
		"%{prj.name}/Vendors/spdlog/include",
		"%{prj.name}/Vendors/GLM",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.YAML}",
	}

	links {
		"Glad",
		"ImGUI",
		"GLFW",
		"opengl32.lib",
		"YAML",
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ME_PLATFORM_WINDOWS",
			"ME_BUILD_DLL"
		}

		-- postbuildcommands {
		-- 	("{COPY} %{cfg.buildtarget.relpath} ../Sandbox/Binaries/" .. outputdir)
		-- }

		filter "configurations:DevEditor"
			defines {
				"ME_WITH_EDITOR",
				"ME_BUILD_DEBUG",
			}
			buildoptions "/MDd"
			symbols "on"

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
	"Mimou/Vendors/GLM",
	"%{IncludeDir.ImGUI}",
	"%{IncludeDir.Glad}",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.stb_image}",
	"%{IncludeDir.EnTT}",
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

			
project "MimouEditor"
	kind "ConsoleApp"
	language "C++"
	location "MimouEditor"
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
		"_CRT_SECURE_NO_WARNINGS",
		"ME_WITH_EDITOR",
	}

	includedirs {
		"%{prj.name}/Source",
		"Mimou/Source",
		"Mimou/Vendors/spdlog/include",
		"Mimou/Vendors/GLM",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.YAML}",
	}

	links {
		"Mimou"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ME_PLATFORM_WINDOWS"
		}

		filter "configurations:DevEditor"
			defines {
				"ME_WITH_EDITOR",
				"ME_BUILD_DEBUG",
			}
			buildoptions "/MDd"
			symbols "on"

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
			