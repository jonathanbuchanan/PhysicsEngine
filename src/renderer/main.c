#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void clear();
void swapBuffers();

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

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
  clear();
  swapBuffers(window);
  glfwPollEvents();
  return window;
}

void terminate() {
  glfwTerminate();
}


void clear() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void swapBuffers(GLFWwindow *window) {
  glfwSwapBuffers(window);
}

