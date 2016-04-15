workspace "Vanilla"
	configurations {"Debug", "Release"}

project "Vanilla" -- project name
	kind "ConsoleApp" -- what's the kind
	language "C++" 
	targetdir "bin/"

	files {"*.cpp", "*.h", "*hpp"}
	files {"utils/**.cpp", "utils/**.hpp"}
	files {"utils/**.h"}
	files {"net/**.cpp", "net/**.h", "net/**.hpp"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"