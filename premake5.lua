
workspace "Zombie-Mall"
    language "C++"
    configurations { "Debug", "Release", "Dist" }

    outputDir = "Build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Zombie-Mall"
        location "Zombie-Mall"
        kind "WindowedApp"
        architecture "x86_64"
        targetdir (outputDir .. "/%{prj.name}/Bin")
        objdir (outputDir .. "/%{prj.name}/Obj")

        files { "%{prj.name}/**.h", "%{prj.name}/**.cpp" }

        filter "configurations:Debug"
            symbols "On"
            defines { "DEBUG", "DEBUG_RENDER" }
            libdirs
            {
                "Vendor/SFML/Libs",
                "Vendor/Lua/Lib/x64"
            }
            links
            {
                "sfml-audio-d",
                "sfml-graphics-d",
                "sfml-main-d",
                "sfml-system-d",
                "sfml-window-d",
                "LuaLibsD"
            }
            includedirs
            {
                "Vendor/Lua/Include",
                "Vendor/LuaBridge/Include",
                "Vendor/RapidJSON/Include",
                "Vendor/SFML/Include"
            }

        filter "configurations:Release"
            symbols "On"
            optimize "On"
            defines { "NDEBUG" }
            libdirs
            {
                "Vendor/SFML/Libs",
                "Vendor/Lua/Lib/x64"
            }
            links
            {
                "sfml-audio",
                "sfml-graphics",
                "sfml-main",
                "sfml-system",
                "sfml-window",
                "LuaLibs"
            }
            includedirs
            {
                "Vendor/Lua/Include",
                "Vendor/LuaBridge/Include",
                "Vendor/RapidJSON/Include",
                "Vendor/SFML/Include"
            }

        filter "configurations:Dist"
            optimize "On"
            defines { "NDEBUG" }
            libdirs
            {
                "Vendor/SFML/Libs",
                "Vendor/Lua/Lib/x64"
            }
            links
            {
                "sfml-audio",
                "sfml-graphics",
                "sfml-main",
                "sfml-system",
                "sfml-window",
                "LuaLibs"
            }
            includedirs
            {
                "Vendor/Lua/Include",
                "Vendor/LuaBridge/Include",
                "Vendor/RapidJSON/Include",
                "Vendor/SFML/Include"
            }

        filter "system:windows"
            defines { "ZM_WINDOWS" }
            cppdialect "C++17"
            systemversion "latest"