
include "Dependencies.lua"

outputTargetDir = "Build/%{cfg.platform}-%{cfg.buildcfg}/Bin"
outputObjDir = "Build/%{cfg.platform}-%{cfg.buildcfg}/Obj"

workspace "ZombieMaul"
    configurations { "Debug", "Release", "Dist" }
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"

    filter { "system:windows" }
        defines { "ZM_WINDOWS" }
        systemversion "latest"

include "LuaLib"
include "ZombieMaul"
