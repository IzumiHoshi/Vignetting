cmake_minimum_required(VERSION 3.11)

set(TARGET_NAME Vignetting)

project(${TARGET_NAME} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

find_package(OpenMP REQUIRED)

add_library(${TARGET_NAME} 
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${TARGET_NAME} PRIVATE
    OpenMP::OpenMP_CXX
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})


add_subdirectory(Example)
