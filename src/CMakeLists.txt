cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fexec-charset=GBK")

# find sources
add_subdirectory(model/identity_model)
add_executable(
	${PROJECT_NAME}
	global_file.h
	main.cpp
)
target_link_libraries(
	${PROJECT_NAME}
	identity_model
)