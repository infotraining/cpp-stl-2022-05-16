##############
# Vcpkg integration - uncomment if necessery
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

get_filename_component(PROJECT_NAME_STR ${CMAKE_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${PROJECT_NAME_STR})

cmake_minimum_required(VERSION 3.8)
project(${PROJECT_NAME_STR})

#----------------------------------------
# Application
#----------------------------------------
aux_source_directory(. SRC_LIST)

find_package(Threads REQUIRED)
find_package(TBB CONFIG REQUIRED)


# Headers
file(GLOB HEADERS_LIST "*.h" "*.hpp")
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb Threads::Threads)

#----------------------------------------
# Tests
#----------------------------------------
enable_testing()
add_test(tests ${PROJECT_NAME})
