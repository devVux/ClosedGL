
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
 

set(PROJECT_NAME "Editor")
set(IMGUI_SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/imgui")

project(${PROJECT_NAME})

find_package(glfw3 REQUIRED)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/ClosedGL/include"
	"${CMAKE_SOURCE_DIR}/ClosedGL/include/ClosedGL/Utils"
	"${CMAKE_SOURCE_DIR}/vendor/imgui"
	"${CMAKE_SOURCE_DIR}/vendor/imgui/misc/cpp"
	"${CMAKE_SOURCE_DIR}/vendor/imguiFileDialog"
	"${CMAKE_SOURCE_DIR}/vendor/ImGuiIcons"
)

set(SOURCES
 	
	"include/Editor.cpp" 
	"include/SceneView.cpp" 
	"include/SceneHierarchy.cpp" 
	"include/Inspector.cpp" 
	"include/Toolbar.cpp" 


    "${IMGUI_SOURCE_DIR}/imgui.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_demo.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_draw.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_tables.cpp"
    "${IMGUI_SOURCE_DIR}/imgui_widgets.cpp"
    "${IMGUI_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp"

    "${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
    "${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"

	"${CMAKE_SOURCE_DIR}/vendor/imguiFileDialog/ImGuiFileDialog.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC ClosedGLStatic -FORCE:MULTIPLE)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${STATICLIB} PROPERTY CXX_STANDARD 20)
endif()