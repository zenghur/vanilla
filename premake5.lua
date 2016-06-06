workspace "Vanilla"
	configurations {"Debug", "Release"}

project "Vanilla" -- project name
	kind "ConsoleApp" -- what's the kind
	language "C++" 
	targetdir "bin/"
	includedirs {"shared/**"}
	files {"*.cpp", "*.h", "*hpp"}
	files {"utils/**.cpp", "utils/**.hpp"}
	files {"utils/**.h"}
	files {"net/**.cpp", "net/**.h", "net/**.hpp"}
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