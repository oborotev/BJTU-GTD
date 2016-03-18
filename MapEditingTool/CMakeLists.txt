cmake_minimum_required(VERSION 3.3)
project(MapEditingTool)

# Set executable name
set(EXECUTABLE_NAME MapEditor)

# SFML on  Windows
if(WIN32)
    set(SFML_ROOT "C:\\SFML")
endif(WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(BEFORE ${MY_SOURCE_DIR}includes/)

# Output directory
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

set(SOURCE_FILES src/main.cpp src/graphicHandler.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../common/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

