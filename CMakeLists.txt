cmake_minimum_required(VERSION 3.2.2)
project(sdss_asteroid_detect)

set (ML_UTIL_VERSION_MAJOR 0)
set (ML_UTIL_VERSION_MINOR 1)
set (ML_UTIL_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake-modules)

include(CTest)

include(DownloadProject.cmake)

download_project(PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

download_project(PROJ                rapidjson
        GIT_REPOSITORY      https://github.com/miloyip/rapidjson.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

download_project(PROJ                gnuplot-cpp
        GIT_REPOSITORY      https://github.com/orbitcowboy/gnuplot-cpp.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

download_project(PROJ                loguru
        GIT_REPOSITORY      https://github.com/emilk/loguru.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

download_project(PROJ                OpenCV
        GIT_REPOSITORY      https://github.com/opencv/opencv.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

download_project(PROJ                curl
        GIT_REPOSITORY      https://github.com/curl/curl.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

#include_directories(${curl_SOURCE_DIR}/include)
include_directories(${rapidjson_SOURCE_DIR}/include)
include_directories(${gnuplot-cpp_SOURCE_DIR})
include_directories(${loguru_SOURCE_DIR})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package( curl REQUIRED )
include_directories( ${curl_INCLUDE_DIRS} )

# setup gtest testing
enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
if(NOT DISABLE_TESTS)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# tests
add_executable(runAllTests test/unit_test_main.cpp)
target_link_libraries(runAllTests gtest gmock_main pthread ${OpenCV_LIBS} ${curl_LIBS})
add_test( runTests build/runAllTests )

# build command line utilities
set(NAIVE_DETECT_SOURCE_FILES src/naive_detect/main.cpp)
add_executable(naive_detect ${NAIVE_DETECT_SOURCE_FILES})
target_link_libraries(naive_detect ${OpenCV_LIBS} ${curl_LIBS})

set(VIDEO_DETECT_SOURCE_FILES src/example_video_test.cpp)
add_executable(video_test ${VIDEO_DETECT_SOURCE_FILES})
target_link_libraries(video_test ${OpenCV_LIBS} ${curl_LIBS})

# define what to include in release
install(TARGETS ${INS_TARGETS}
        RUNTIME DESTINATION bin COMPONENT applications
        LIBRARY DESTINATION lib COMPONENT libraries
        ARCHIVE DESTINATION lib COMPONENT libraries
        )

install(TARGETS naive_detect RUNTIME DESTINATION bin COMPONENT applications)

# cpack defs
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL applications)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "sdss asteroid detect")
set(CPACK_PACKAGE_VENDOR "James Fuller")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${ML_UTIL_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${ML_UTIL_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${ML_UTIL_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "RPM")
include(CPack)