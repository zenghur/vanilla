workspace "Vanilla"
	configurations {"Debug", "Release"}

project "Vanilla" -- project name
	kind "ConsoleApp" -- what's the kind
	language "C++" 
	targetdir "bin/"
	includedirs {"shared/"}
	includedirs {"net/"}
	includedirs {"utils/"}
	includedirs {"./"}

	files {"*.cpp", "*.h"}
	files {"utils/**.cpp"}
	files {"utils/**.h"}
	files {"net/**.cpp", "net/**.h"}
	files {"shared/glog/**.h"}
	libdirs {"shared/libs/"}
	--links {"glog"}
	buildoptions {"-std=c++11"}
	filter "configurations:Debug"
		defines {"DEBUG"}
		flags {"Symbols"}

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"

	