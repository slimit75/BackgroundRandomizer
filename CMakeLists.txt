cmake_minimum_required(VERSION 3.9.1)
project(BackgroundRandomizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -fPIC -fvisibility=hidden -std=c++17 -Wno-narrowing")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 64)

add_executable(BackgroundRandomizer src/plugin.cpp)
set_target_properties(BackgroundRandomizer PROPERTIES SUFFIX ".xpl")

add_definitions(-DXPLM200)
add_definitions(-DXPLM210)
add_definitions(-DXPLM300)
add_definitions(-DXPLM301)
add_definitions(-DXPLM302)
add_definitions(-DXPLM303)

include_directories("libs/XSDK/CHeaders/XPLM")
include_directories("libs/XSDK/CHeaders/Widgets")

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set_target_properties(BackgroundRandomizer PROPERTIES OUTPUT_NAME "win")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static -shared -Wl,--version-script=exports.txt")
    add_definitions(-DIBM)

    include_directories("libs/libacfutils/win64/include")

    target_link_libraries(BackgroundRandomizer
		XPLM_64
		XPWidgets_64
		stdc++
    )
endif (CMAKE_SYSTEM_NAME MATCHES "Windows")
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set_target_properties(BackgroundRandomizer PROPERTIES OUTPUT_NAME "apl")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared -Wl,-exported_symbol -Wl,_XPluginStart -Wl,-exported_symbol -Wl,_XPluginEnable -Wl,-exported_symbol -Wl,_XPluginReceiveMessage -Wl,-exported_symbol -Wl,_XPluginDisable -Wl,-exported_symbol -Wl,_XPluginStop")
    add_definitions(-DAPL)

    include_directories("libs/libacfutils/mac64/include")

    target_link_libraries(BackgroundRandomizer
        XPLM
        XPWidgets
        stdc++
    )
endif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set_target_properties(BackgroundRandomizer PROPERTIES OUTPUT_NAME "lin")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -shared -Wl,--version-script=exports.txt")
    add_definitions(-DLIN)

    target_link_libraries(BackgroundRandomizer stdc++)
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")