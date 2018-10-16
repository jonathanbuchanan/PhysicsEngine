#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct RenderInfo {
  GLuint shaderProgram;
} RenderInfo;

RenderInfo * createRenderer(GLFWwindow *window);
void render(GLFWwindow *window, RenderInfo *renderer);
void clear(GLFWwindow *window);
void swapBuffers(GLFWwindow *window);
void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha);

#endif
