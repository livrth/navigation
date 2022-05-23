project("identity_model")
cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14) 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fexec-charset=GBK")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 
add_library( 
	${PROJECT_NAME}
	STATIC
	admin.h
	student.h
	teacher.h 
	admin.cpp
	student.cpp
	teacher.cpp
)

target_link_libraries(
	${PROJECT_NAME}
	# homework_model
	course_model
	navigation_model
)
target_include_directories(${PROJECT_NAME} PUBLIC .) #${INCLUDE_DIRECTORIES})
