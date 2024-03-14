
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
 

set(PROJECT_NAME "ClosedGL")
set(STATICLIB "ClosedGLStatic")

project(${PROJECT_NAME})

find_package(spdlog REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(EnTT REQUIRED)
find_package(stb REQUIRED)

enable_testing()
include_directories(
    "${PROJECT_SOURCE_DIR}/test"
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Core"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Core/Managers"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Events"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Layers"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Renderer"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Scene"
    "${PROJECT_SOURCE_DIR}/include/ClosedGL/Utils"
)

set(SOURCES
	
	"include/pch.cpp"

	"include/ClosedGL/Core/Application.cpp"
	"include/ClosedGL/Core/Log.cpp"

	"include/ClosedGL/Core/Window.cpp"
	"include/ClosedGL/Core/Input.cpp"

	"include/ClosedGL/Core/Managers/Managers.cpp"

	"include/ClosedGL/Layers/LayerStack.cpp"

	"include/ClosedGL/Renderer/Buffer.cpp"
	"include/ClosedGL/Renderer/Renderer2D.cpp"
	"include/ClosedGL/Renderer/Shader.cpp"
	"include/ClosedGL/Renderer/Texture.cpp"

	"include/ClosedGL/Scene/Scene.cpp"
	"include/ClosedGL/Scene/OrthographicCamera.cpp"
	"include/ClosedGL/Scene/PerspectiveCamera.cpp"


)	

add_library(${STATICLIB} STATIC ${SOURCES})

target_link_directories(${STATICLIB} PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(${STATICLIB} PUBLIC spdlog::spdlog)
target_link_libraries(${STATICLIB} PUBLIC glfw)
target_link_libraries(${STATICLIB} PUBLIC glad::glad)
target_link_libraries(${STATICLIB} PUBLIC glm::glm)
target_link_libraries(${STATICLIB} PUBLIC EnTT::EnTT)
target_link_libraries(${STATICLIB} PRIVATE PhysiksStatic) 
target_link_libraries(${STATICLIB} PRIVATE GTest::gtest_main)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${STATICLIB})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${STATICLIB} PROPERTY CXX_STANDARD 20)
endif()