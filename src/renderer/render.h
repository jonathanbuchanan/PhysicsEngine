#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "model.h"

typedef GLuint ShaderProgram;

typedef struct RenderInfo {
  // Two shaders
  ShaderProgram shader3D;
  ShaderProgram shader2D;

  Model model;
} RenderInfo;

RenderInfo * createRenderer(GLFWwindow *window);
void freeRenderer(RenderInfo *renderer);
void render(GLFWwindow *window, RenderInfo *renderer);
void clear(GLFWwindow *window);
void swapBuffers(GLFWwindow *window);
void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha);

#endif
