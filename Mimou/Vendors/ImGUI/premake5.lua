project "ImGUI"
    kind "StaticLib"
    language "C++"

    targetdir ("%{prj.name}/Binaries/" .. outputdir)
    objdir ("%{prj.name}/Intermediate/" .. outputdir)

    files
    {
        "**.h",
        "**.cpp"
    }

	includedirs {
        "%{prj.path}",
        "%{prj.path}/../GLFW/include"
	}

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
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