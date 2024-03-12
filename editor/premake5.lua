
IncludeDir = {}
IncludeDir["ImGui"] = "3rdParty/imgui/"
IncludeDir["GLFW"] = "3rdParty/GLFW/include/"
IncludeDir["glad"] = "3rdParty/glad/include/"
IncludeDir["imfilebrowser"] = "3rdParty/imfilebrowser/"
IncludeDir["stb"] = "3rdParty/stb/"

include "3rdParty/imgui/" 
include "3rdParty/GLFW/"
include "3rdParty/glad/"

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
       "%{IncludeDir.imfilebrowser}",
       "%{IncludeDir.stb}",
       "%{IncludeDir.glad}",
    }
    links {
      "GLFW",
      "glad",
      "-lglfw3",
      "ImGui",
      "GL",

    }

