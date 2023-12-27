workspace "Logger"
  configurations {"Debug", "Release", "Dist"}

project "log"
  kind "ConsoleApp"
  language "C"
  cdialect "C17"

  targetdir "%{wks.location}/bin/"
  objdir "%{wks.location}/bin/int/"

  files {
    "main.c",
    "../log.h"
  }

  filter {"configurations:Debug"}
    defines {"DEBUG"}
    symbols "on"
    
  filter {"configurations:Release"}
    optimize "on"

  filter {"configurations:Release"}
    optimize "full"
 
  filter {""}
