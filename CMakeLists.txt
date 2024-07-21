
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project("ClosedGL")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories("${CMAKE_SOURCE_DIR}/ClosedGL/include")
include_directories("${CMAKE_SOURCE_DIR}/vendor/Physiks/include")

add_subdirectory(ClosedGL)
add_subdirectory(Sandbox)
add_subdirectory(vendor/Physiks)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ClosedGL PROPERTY CXX_STANDARD 20)
endif()

