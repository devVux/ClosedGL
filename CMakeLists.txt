
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

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

