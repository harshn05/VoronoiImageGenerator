cmake_minimum_required(VERSION 3.10)
project(Voronoi)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP REQUIRED)

set(STB_IMAGE_WRITE_URL "https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h")
set(STB_IMAGE_WRITE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/stb_image_write.h")

if(NOT EXISTS ${STB_IMAGE_WRITE_FILE})
    file(DOWNLOAD ${STB_IMAGE_WRITE_URL} ${STB_IMAGE_WRITE_FILE}
         SHOW_PROGRESS
         STATUS status
         LOG log)

    list(GET status 0 status_code)
    list(GET status 1 status_string)

    if(NOT status_code EQUAL 0)
        message(FATAL_ERROR "Error downloading file: ${status_string}")
    endif()
endif()

add_executable(Voronoi main.cpp)

target_include_directories(Voronoi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Voronoi PRIVATE OpenMP::OpenMP_CXX)