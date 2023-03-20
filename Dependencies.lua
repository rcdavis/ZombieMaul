
IncludeDir = {}
IncludeDir["Lua"] = "%{wks.location}/LuaLib/src"
IncludeDir["LuaBridge"] = "%{wks.location}/Vendor/LuaBridge/src"
IncludeDir["rapidjson"] = "%{wks.location}/Vendor/RapidJSON/src"
IncludeDir["sfml"] = "%{wks.location}/Vendor/SFML/src"

Library = {}
Library["sfml_main"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-main.lib"
Library["sfml_system"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-system.lib"
Library["sfml_window"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-window.lib"
Library["sfml_graphics"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-graphics.lib"
Library["sfml_audio"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-audio.lib"

Library["sfml_system_dll"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-system-2.dll"
Library["sfml_window_dll"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-window-2.dll"
Library["sfml_graphics_dll"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-graphics-2.dll"
Library["sfml_audio_dll"] = "%{wks.location}/Vendor/SFML/lib/%{cfg.platform}-%{cfg.buildcfg}/sfml-audio-2.dll"
