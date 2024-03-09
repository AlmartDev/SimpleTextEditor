
IncludeDir = {}
IncludeDir["ImGui"] = "3rdParty/imgui/"
--IncludeDir["glad"] = "3rdParty/glad/include"
IncludeDir["GLFW"] = "3rdParty/GLFW/include/"

include "3rdParty/imgui/"
include "3rdParty/GLFW/"
--include "3rdParty/glad"

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
       --"%{IncludeDir.glad}",
    }
    links {
      "GLFW",
      "-lglfw3",
      "ImGui",
      --"glad",
      "GL",

    }

