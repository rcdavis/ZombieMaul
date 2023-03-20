
project "ZombieMaul"
    language "C++"
    cppdialect "C++17"
    targetdir (outputTargetDir)
    objdir (outputObjDir)

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "%{IncludeDir.Lua}",
        "%{IncludeDir.LuaBridge}",
        "%{IncludeDir.rapidjson}",
        "%{IncludeDir.sfml}"
    }

    links {
        "LuaLib",
        "%{Library.sfml_main}",
        "%{Library.sfml_system}",
        "%{Library.sfml_window}",
        "%{Library.sfml_graphics}",
        "%{Library.sfml_audio}"
    }

    filter { "configurations:Debug" }
        kind "ConsoleApp"
        symbols "On"
        defines { "DEBUG", "DEBUG_RENDER" }

    filter { "configurations:Release or configurations:Dist" }
        optimize "On"
        defines { "NDEBUG" }

    filter { "configurations:Release" }
        kind "ConsoleApp"
        symbols "On"

    filter { "configurations:Dist" }
        kind "WindowedApp"