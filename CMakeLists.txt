cmake_minimum_required(VERSION 3.12)

SET(PROJECT_NAME Viewer)
project(${PROJECT_NAME})

if(MSVC)
	 add_compile_options(/MP)
endif()

add_subdirectory(ViewerCore)
