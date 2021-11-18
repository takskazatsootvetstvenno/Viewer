cmake_minimum_required(VERSION 3.12)

set(CORE_PROJECT_NAME ViewerCore)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CORE_INCLUDES
	includes/Application.h
	includes/BufferLayout.h
	includes/ConsoleWidget.h
	includes/Event.h
	includes/Game.h
	includes/IndexBuffer.h
	includes/LogManager.h
	includes/Mesh.h
	includes/Model.h
	includes/ResourceManager.h
	includes/ShaderProgram.h
	includes/Texture.h
	includes/UniformBuffer.h
	includes/VertexArray.h
	includes/VertexBuffer.h
	includes/Window.h
	bindings/imgui_impl_glfw.h
    bindings/imgui_impl_opengl3.h
	bindings/imgui_impl_opengl3_loader.h
)
set(CORE_SOURCES
	sources/Application.cpp
	sources/BufferLayout.cpp
	sources/ConsoleWidget.cpp
	sources/Game.cpp
	sources/IndexBuffer.cpp
	sources/LogManager.cpp
	sources/main.cpp
	sources/Mesh.cpp
	sources/Model.cpp
	sources/ResourceManager.cpp
	sources/ShaderProgram.cpp
	sources/Texture.cpp
	sources/UniformBuffer.cpp
	sources/VertexArray.cpp
	sources/VertexBuffer.cpp
	sources/Window.cpp
	bindings/imgui_impl_glfw.cpp
    bindings/imgui_impl_opengl3.cpp
)
add_executable(${CORE_PROJECT_NAME}
	${CORE_INCLUDES}
	${CORE_SOURCES}
)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE src)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE bindings)

target_link_libraries(${CORE_PROJECT_NAME} ${CONAN_LIBS})

add_custom_command(TARGET ${CORE_PROJECT_NAME}
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Shaders/General.frag ${PROJECT_BINARY_DIR}/ViewerCore/Shaders/General.frag
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Shaders/General.vert ${PROJECT_BINARY_DIR}/ViewerCore/Shaders/General.vert
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Shaders/Red.frag ${PROJECT_BINARY_DIR}/ViewerCore/Shaders/Red.frag
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Shaders/Red.vert ${PROJECT_BINARY_DIR}/ViewerCore/Shaders/Red.vert
	
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Models/map.mtl ${PROJECT_BINARY_DIR}/ViewerCore/Models/map.mtl 
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Models/map.obj ${PROJECT_BINARY_DIR}/ViewerCore/Models/map.obj
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/data/Models/wood.jpg ${PROJECT_BINARY_DIR}/ViewerCore/Models/wood.jpg
)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_compile_definitions(CMAKE_BUILD_TYPE_RELEASE)
	message("It is Release!" )
else()
	add_compile_definitions(CMAKE_BUILD_TYPE_DEBUG)
	message("It is Debug!" )
endif()

install(TARGETS ${CORE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/install)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/Shaders DESTINATION ${CMAKE_INSTALL_PREFIX}/install)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/Models DESTINATION ${CMAKE_INSTALL_PREFIX}/install)