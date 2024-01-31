
set(PROJECT_NAME "ClosedGLTest")

find_package(GTest REQUIRED)

set(SOURCES
	tests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest)


add_test(custom_gtests ${PROJECT_NAME})