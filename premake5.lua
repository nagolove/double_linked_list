workspace "double_linked_list"
    configurations { "Debug", "Release" }
    includedirs { 
    }
    buildoptions { 
        "-ggdb3",
        --"-o3",
        "-fPIC",
        "-Wall",
        --"-Werror",
        --"-Wextra",
        "-Wno-strict-aliasing",
        --"--stack,8388608",
        --"--stack,16777216",
        --"--stack,33554432",
        --"-Wl,--stack,33554432",
        --"--mstack-size 67108864",
        --"-Wno-unused-function",
        --"-Wno-unused-parameter",
    }
    links { 
        "m",
    }
    libdirs { 
    }
    language "C"
    kind "ConsoleApp"
    targetprefix ""
    targetdir "."

    project "init"
        files { 
            "*.h", 
            "*.c",
        }

    filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
