cmake_minimum_required(VERSION 3.7)
project(asteroid_detect)

set (ML_UTIL_VERSION_MAJOR 0)
set (ML_UTIL_VERSION_MINOR 1)
set (ML_UTIL_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 11)

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

#include_directories(${curl_SOURCE_DIR}/include)
include_directories(${rapidjson_SOURCE_DIR}/include)
include_directories(${gnuplot-cpp_SOURCE_DIR})
include_directories(${loguru_SOURCE_DIR})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# setup testing
enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
if(NOT DISABLE_TESTS)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# tests
add_executable(runAllTests test/unit_test_main.cpp)
target_link_libraries(runAllTests gtest gmock_main pthread ${OpenCV_LIBS})
add_test( runTests build/runAllTests )

set(DETECT_SOURCE_FILES src/detect/main.cpp)
add_executable(detect ${DETECT_SOURCE_FILES})

target_link_libraries(detect ${OpenCV_LIBS})

# define what to include in release
install(TARGETS ${INS_TARGETS}
        RUNTIME DESTINATION bin COMPONENT applications
        LIBRARY DESTINATION lib COMPONENT libraries
        ARCHIVE DESTINATION lib COMPONENT libraries
        )
#install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION . COMPONENT applications)
#install(FILES ${CMAKE_SOURCE_DIR}/README.md DESTINATION . COMPONENT applications)
#install(FILES ${CMAKE_SOURCE_DIR}/VERSION DESTINATION . COMPONENT applications)
#install(FILES ${CMAKE_SOURCE_DIR}/etc/.ml-utils DESTINATION . COMPONENT applications)
#install(FILES ${CMAKE_SOURCE_DIR}/etc/.ml-utils DESTINATION etc COMPONENT applications)
#install(FILES ${CMAKE_SOURCE_DIR}/etc/basic.gnuplot DESTINATION etc COMPONENT applications)
#install(FILES ${CMAKE_SOURCE_DIR}/etc/text.gnuplot DESTINATION etc COMPONENT applications)

#install(TARGETS ml-config RUNTIME DESTINATION bin COMPONENT applications)
install(TARGETS detect RUNTIME DESTINATION bin COMPONENT applications)

# cpack defs
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL applications)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Asteroid Detect utilities")
set(CPACK_PACKAGE_VENDOR "James Fuller")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${ML_UTIL_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${ML_UTIL_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${ML_UTIL_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "RPM")
include(CPack)