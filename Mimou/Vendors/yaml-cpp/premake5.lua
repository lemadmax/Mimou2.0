project "YAML"
    kind "StaticLib"
    language "C++"

    targetdir ("%{prj.name}/Binaries/" .. outputdir)
    objdir ("%{prj.name}/Intermediate/" .. outputdir)

    files
    {
		"src/**.h",
		"src/**.cpp",
        "include/**.h",
    }

	includedirs {
		"include",
	}

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        cdialect "C11"
        staticruntime "on"

    filter "configurations:Debug"
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        symbols "on"

    filter "configurations:Dist"
        runtime "Release"
        symbols "on"