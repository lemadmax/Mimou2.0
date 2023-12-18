project "YAML"
    kind "StaticLib"
    language "C++"

    targetdir ("%{prj.name}/Binaries/" .. outputdir)
    objdir ("%{prj.name}/Intermediate/" .. outputdir)

    files
    {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/contrib/**.h",
		"%{prj.name}/src/contrib/**.cpp",
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++20"
        staticruntime "on"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        symbols "on"

    filter "configurations:Dist"
        runtime "Release"
        symbols "on"