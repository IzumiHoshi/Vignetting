cmake_minimum_required(VERSION 3.11)


# set(OpenCV_DIR "$ENV{OpenCV_ROOT}\\x64\\vc16\\lib" CACHE FILEPATH "Set to find OpenCV")
# find_package(OpenCV CONFIG REQUIRED NO_DEFAULT_PATH)

add_executable(TestVignetting 
    TestVignetting.cpp
)

target_link_libraries(TestVignetting
    Vignetting::Vignetting
)
