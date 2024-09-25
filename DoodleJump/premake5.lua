project "DoodleJump"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "Source/Core",
        "Source/Game",
        "%{IncludeDir.Framework}"
    }

    libdirs
    {
        "%{wks.location}/ThirdParty/Framework/lib"
    }

    links
    {
        "FrameworkRelease_x64"
    }

    targetdir ("%{wks.location}/Build/Binaries/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/Build/Intermediate/" .. outputdir .. "/%{prj.name}")

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