#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "render.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}



// Functions exposed to the Julia wrapper
int init() {
  if (!glfwInit())
    return -1;

  glfwSetErrorCallback(error_callback);

  glewExperimental = 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  return 0;
}

GLFWwindow * createWindow(int width, int height, char *title) {
  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL)
    return NULL;
  glfwMakeContextCurrent(window);
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK)
    return NULL;

  setClearColor(window, 0.133, 0.776, 0.776, 1.0);

  return window;
}

int windowCloseStatus(GLFWwindow *window) {
  return glfwWindowShouldClose(window);
}

void terminate(RenderInfo *renderer) {
  glfwTerminate();
  freeRenderer(renderer);
}

