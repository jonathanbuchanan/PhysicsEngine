project(PhysicsEngineRenderer C)
add_library(physicsenginerenderer SHARED main.c)

find_package(glfw3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})
target_link_libraries(physicsenginerenderer glfw3)

find_package(glew REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
target_link_libraries(physicsenginerenderer glew)

if(APPLE)
  find_package(OpenGL REQUIRED)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries(physicsenginerenderer ${OPENGL_LIBRARIES}) 

  target_link_libraries(physicsenginerenderer "-framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo")
else()

endif()
