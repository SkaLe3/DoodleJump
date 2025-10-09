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

    local targetDir = "%{wks.location}/Build/Binaries/" .. outputdir .. "/%{prj.name}"
    targetdir (targetDir)
    objdir ("%{wks.location}/Build/Intermediate/" .. outputdir .. "/%{prj.name}")

    filter "system:windows"
        defines { "_WINDOWS"}
        systemversion "latest"

        postbuildcommands
        {
            "copy \"%{wks.location}/ThirdParty/Framework/bin\\*.*\" \"" .. targetDir .. "\\\""
        }

        postbuildcommands
        {
            "xcopy \"%{prj.location}/Content\" \"" .. targetDir .. "\\Content\" /E /I /Y"
        }



    filter "action:vs*"
        flags { "MultiProcessorCompile" }  -- Enables /MP flag for MSVC

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