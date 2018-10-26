#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "model.h"
#include "menu.h"

#define GLYPH_COUNT 128

typedef struct Glyph {
  GLuint textureID;
  Vector2 size;
  Vector2 bearing;
  double advance;
} Glyph;

typedef GLuint ShaderProgram;
typedef struct RenderInfo {
  GLFWwindow *window;

  FT_Library fontLibrary;
  FT_Face fontFace;
  Glyph glyphs[GLYPH_COUNT];

  // Shaders
  ShaderProgram shader3D;
  ShaderProgram shader2D;
  ShaderProgram shader2DTextured;

  Model model;

  Shape quad2D; // The quad used for 2D rendering
  Menu menu;
} RenderInfo;

RenderInfo * createRenderer(GLFWwindow *window);
void freeRenderer(RenderInfo *renderer);
void render(RenderInfo *renderer);
void renderQuad(RenderInfo *renderer, Vector2 size, Vector2 position, Vector4 color, double z);
void renderText(RenderInfo *renderer, const char *text, Vector2 position, Vector4 color, double z);

Vector2 getWindowSize(const RenderInfo *renderer);
Vector2 getCursorPosition(const RenderInfo *renderer);
int isLeftMouseButtonPressed(const RenderInfo *renderer);
void clear(GLFWwindow *window);
void swapBuffers(GLFWwindow *window);
void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha);

#endif
