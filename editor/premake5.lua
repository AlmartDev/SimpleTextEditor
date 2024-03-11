
IncludeDir = {}
IncludeDir["ImGui"] = "3rdParty/imgui/"
IncludeDir["GLFW"] = "3rdParty/GLFW/include/"

include "3rdParty/imgui/" 
include "3rdParty/GLFW/"

project "editor"
    kind "StaticLib"
    language "C++"

    files {
       "**.h",
       "**.hpp",
       "**.cc",
       "**.cpp",
    }
    includedirs {
       "%{IncludeDir.GLFW}",
       "%{IncludeDir.ImGui}",
    }
    links {
      "GLFW",
      "-lglfw3",
      "ImGui",
      "GL",

    }

