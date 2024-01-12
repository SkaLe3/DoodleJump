workspace "DoodleJump"
    architecture "x64"
    startproject "DoodleJump"
    configurations{ "Debug", "Release" }

outputdir = "%{cgf.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Framework"] = "vendor/Framework/include"

include "DoodleJump"