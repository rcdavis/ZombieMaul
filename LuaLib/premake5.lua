
project "LuaLib"
	kind "StaticLib"
	language "C"
    staticruntime "off"

	targetdir (outputTargetDir)
    objdir (outputObjDir)

	files {
		"src/*.h",
		"src/*.hpp",
		"src/*.c"
	}

	includedirs {
		"src"
    }
