cmake_minimum_required(VERSION 3.3)
project(MeiYouCommunication)

# Set executable name
set(EXECUTABLE_NAME MeiYouCommunication)

# SFML on  Windows
if(WIN32)
    set(SFML_ROOT "C:\\SFML")
endif(WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(BEFORE ${MY_SOURCE_DIR}includes/)

set(SOURCE_FILES src/main.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

