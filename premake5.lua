workspace "Vanilla"
	configurations {"Debug", "Release"}

project "Vanilla" -- project name
	kind "ConsoleApp" -- what's the kind
	language "C++" 
	targetdir "bin/"

	files {"*.cpp", "*.h"}
	files {"utils/**.cpp"}
	files {"utils/**.h"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"