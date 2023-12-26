project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{prj.name}/Binaries/" .. outputdir)
    objdir ("%{prj.name}/Intermediate/" .. outputdir)

    files
    {
        "src/glad.c",
    }

    includedirs
    {
        "include",
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter "configurations:DevEditor"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        symbols "on"

    filter "configurations:Dist"
        runtime "Release"
        symbols "on"