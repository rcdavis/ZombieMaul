
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
        postbuildcommands {
            "{COPY} %{Library.sfml_system_dll_d} %{outputTargetDir}",
            "{COPY} %{Library.sfml_window_dll_d} %{outputTargetDir}",
            "{COPY} %{Library.sfml_graphics_dll_d} %{outputTargetDir}",
            "{COPY} %{Library.sfml_audio_dll_d} %{outputTargetDir}"
        }

    filter { "configurations:Release or configurations:Dist" }
        optimize "On"
        defines { "NDEBUG" }
        postbuildcommands {
            "{COPY} %{Library.sfml_system_dll} %{outputTargetDir}",
            "{COPY} %{Library.sfml_window_dll} %{outputTargetDir}",
            "{COPY} %{Library.sfml_graphics_dll} %{outputTargetDir}",
            "{COPY} %{Library.sfml_audio_dll} %{outputTargetDir}"
        }

    filter { "configurations:Release" }
        kind "ConsoleApp"
        symbols "On"

    filter { "configurations:Dist" }
        kind "WindowedApp"
