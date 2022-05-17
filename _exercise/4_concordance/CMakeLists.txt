get_filename_component(PROJECT_NAME_STR ${CMAKE_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${PROJECT_NAME_STR})

set(CMAKE_BUILD_TYPE "Release")

cmake_minimum_required(VERSION 2.8)
project(${PROJECT_NAME_STR})

#----------------------------------------
# Libraries
#----------------------------------------
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

#----------------------------------------
# Application
#----------------------------------------

# Sources
aux_source_directory(. SRC_LIST)

# Headers
file(GLOB HEADERS_LIST "*.h" "*.hpp")

# Application
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})

# Setting C++ standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
target_link_libraries(${PROJECT_NAME} Threads::Threads Boost::boost)

#----------------------------------------
# Resources
#----------------------------------------
file(COPY tokens.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
