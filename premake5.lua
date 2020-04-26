
workspace "Zombie-Mall"
    language "C++"
    configurations { "Debug", "Release", "Dist" }
    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "windows"
        architecture "x86_64"

    filter { "system:windows" }
        defines { "ZM_WINDOWS" }
        cppdialect "C++17"
        systemversion "latest"

    outputDir = "Build/%{cfg.buildcfg}-%{cfg.platform}"

    project "Zombie-Mall"
        location "Zombie-Mall"
        targetdir (outputDir .. "/%{prj.name}/Bin")
        objdir (outputDir .. "/%{prj.name}/Obj")

        files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }

        includedirs {
            "Vendor/Lua/Include",
            "Vendor/LuaBridge/Include",
            "Vendor/RapidJSON/Include",
            "Vendor/SFML/Include"
        }

        libdirs { "Vendor/SFML/Libs" }

        filter { "platforms:Win64" }
            libdirs { "Vendor/Lua/Lib/x64" }

        filter { "configurations:Debug" }
            kind "ConsoleApp"
            symbols "On"
            defines { "DEBUG", "DEBUG_RENDER" }
            links {
                "sfml-audio-d",
                "sfml-graphics-d",
                "sfml-main-d",
                "sfml-system-d",
                "sfml-window-d",
                "LuaLibsD"
            }

        filter { "configurations:Release or configurations:Dist" }
            optimize "On"
            defines { "NDEBUG" }
            links {
                "sfml-audio",
                "sfml-graphics",
                "sfml-main",
                "sfml-system",
                "sfml-window",
                "LuaLibs"
            }

        filter { "configurations:Release" }
            kind "ConsoleApp"
            symbols "On"

        filter { "configurations:Dist" }
            kind "WindowedApp"
