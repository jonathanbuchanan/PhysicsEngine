cmake_minimum_required(VERSION 3.12)

project(PhysicsEngineRenderer C)
add_library(physicsenginerenderer SHARED main.c render.c vector.c model.c menu.c camera.c)

set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})
target_link_libraries(physicsenginerenderer glfw3)

find_package(glew REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(physicsenginerenderer glew)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
target_link_libraries(physicsenginerenderer ${FREETYPE_LIBRARIES})

# fontconfig

if(APPLE)
  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries(physicsenginerenderer ${OPENGL_LIBRARIES}) 

  target_link_libraries(physicsenginerenderer "-framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo")
else()

endif()
