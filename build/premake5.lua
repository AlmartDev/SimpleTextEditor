local project_name = "TextEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace (project_name)
    configurations {
       "debug",
       "release",
    }

include "../editor"

project (project_name)
    kind "ConsoleApp" -- Change this!
    links {
      "editor",
      "GLFW",
    }

filter "configurations:debug"
    defines { "DEBUG" }
    buildoptions {
      "-ggdb",
      "-std=c++20",
    }

filter "configurations:release"
    defines { "NDEBUG" }
    buildoptions {
      "-O3",
      "-std=c++20",
      "-march=native",
      "-mtune=native",
    }