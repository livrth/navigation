cmake_minimum_required(VERSION 3.21)

# find sources
file(GLOB_RECURSE SOURCES *.cc)
file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE HPPS *.hpp)


#if(MSVC)
#    target_compile_options(${PROJECT_NAME}_run PRIVATE /W4 /WX)
#else()
#    target_compile_options(${PROJECT_NAME}_run PRIVATE -Wall -Wextra -pedantic)
#endif()