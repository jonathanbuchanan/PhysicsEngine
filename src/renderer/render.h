#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "model.h"
#include "menu.h"

typedef GLuint ShaderProgram;

typedef struct RenderInfo {
  GLFWwindow *window;

  // Two shaders
  ShaderProgram shader3D;
  ShaderProgram shader2D;

  Model model;

  Shape quad2D; // The quad used for 2D rendering
  Menu menu;
} RenderInfo;

RenderInfo * createRenderer(GLFWwindow *window);
void freeRenderer(RenderInfo *renderer);
void render(RenderInfo *renderer);
void renderQuad(RenderInfo *renderer, Vector2 size, Vector2 position, Vector4 color);

Vector2 getWindowSize(const RenderInfo *renderer);
Vector2 getCursorPosition(const RenderInfo *renderer);
void clear(GLFWwindow *window);
void swapBuffers(GLFWwindow *window);
void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha);

#endif
