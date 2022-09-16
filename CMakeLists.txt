cmake_minimum_required(VERSION 3.9.1)
project(BackgroundRandomizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2 -shared -fPIC -pedantic")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 64)
set(CMAKE_BUILD_TYPE Debug)

add_executable(BackgroundRandomizer src/plugin.cpp)
set_target_properties(BackgroundRandomizer PROPERTIES SUFFIX ".xpl")

add_definitions(
    -DXPLM200
    -DXPLM210
    -DXPLM300
    -DXPLM301
    -DXPLM302
    -DXPLM303
)

include_directories(xpdraw
    "libs/XSDK/CHeaders/XPLM"
    "libs/XSDK/CHeaders/Widgets"
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set_target_properties(BackgroundRandomizer PROPERTIES OUTPUT_NAME "win")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--version-script=exports.txt")
    add_definitions(-DIBM)
    target_link_libraries(BackgroundRandomizer
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Win/XPLM_64.lib"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Win/XPWidgets_64.lib"
		stdc++
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set_target_properties(BackgroundRandomizer PROPERTIES OUTPUT_NAME "mac")
    add_definitions(-DAPL)
    target_link_libraries(BackgroundRandomizer
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Mac/XPLM.framework"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/XSDK/Libraries/Mac/XPWidgets.framework"
        "-framework CoreFoundation"
        stdc++
    )
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set_target_properties(BackgroundRandomizer PROPERTIES OUTPUT_NAME "lin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--version-script=exports.txt")
    add_definitions(-DLIN)
    target_link_libraries(BackgroundRandomizer
        stdc++
    )
endif ()