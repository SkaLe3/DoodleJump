project "DoodleJump"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "src/Core",
        "src/Game",
        "%{IncludeDir.Framework}"
    }

    libdirs
    {
        "../vendor/Framework/lib"
    }

    links
    {
        "FrameworkRelease_x64"
    }

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    filter "system:windows"
        defines { "_WINDOWS"}
		systemversion "latest"

	filter "configurations:Debug"
        defines {"D_DEBUG"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines {"D_RELEASE"}
		runtime "Release"
		optimize "on"