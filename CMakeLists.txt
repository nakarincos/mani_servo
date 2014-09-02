cmake_minimum_required (VERSION 2.8)
project (mani-servo)

# The version number.
set (mani-servo_VERSION_MAJOR 0)
set (mani-servo_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
# configure_file (
#  "${PROJECT_SOURCE_DIR}/_config.h.in"
#  "${PROJECT_BINARY_DIR}/_config.h"
#  )


# define library usage
find_package(PkgConfig)
#pkg_check_modules(OPENCV REQUIRED "opencv >= 2.4")

set (DYNAMIXEL_LIB "DXL_SDK_LINUX_v1_01")

set (PTHREAD_LIBRARIES "-lpthread")
set (DXL_LIBRARIES "-ldxl")
#set (EXTRA_LIBS "${DYNAMIXEL_LIB}/lib/libdxl.a")

link_directories(
${PROJECT_SOURCE_DIR}/${DYNAMIXEL_LIB}
)

link_libraries(
${PTHREAD_LIBRARIES}
${DXL_LIBRARIES}
)
 
file(GLOB_RECURSE mani_servo_CXX_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")
 
# complier
set (CMAKE_CXX_COMPILER g++)
add_definitions(-std=c++0x)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

set (CMAKE_CXX_FLAGS_DEBUG, "-g -Wall")
set (CMAKE_CXX_FLAGS "-Wall")


# add the binary tree to the search path for include files
# so that we will find nokkhum_processor_config.h
include_directories ("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/${DYNAMIXEL_LIB}/include")

# add the executable
add_executable (mani-servo ${mani_servo_CXX_SOURCES} )
target_link_libraries (mani-servo)

# add the install targets
install (TARGETS mani-servo DESTINATION bin)
# install (FILES "${PROJECT_BINARY_DIR}/nokkhum_processor_config.h" 
#  DESTINATION include)
