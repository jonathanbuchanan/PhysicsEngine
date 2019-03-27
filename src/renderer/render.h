#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "model.h"
#include "menu.h"
#include "text.h"
#include "camera.h"

typedef enum Key {
  Unknown = -1,
  Space = 32,
  Apostrophe = 39,
  Comma = 44,
  Minus = 45,
  Period = 46,
  Slash = 47,
  Key0 = 48,
  Key1 = 49,
  Key2 = 50,
  Key3 = 51,
  Key4 = 52,
  Key5 = 53,
  Key6 = 54,
  Key7 = 55,
  Key8 = 56,
  Key9 = 57,
  Semicolon = 59,
  Equal = 61,
  KeyA = 65,
  KeyB = 66,
  KeyC = 67,
  KeyD = 68,
  KeyE = 69,
  KeyF = 70,
  KeyG = 71,
  KeyH = 72,
  KeyI = 73,
  KeyJ = 74,
  KeyK = 75,
  KeyL = 76,
  KeyM = 77,
  KeyN = 78,
  KeyO = 79,
  KeyP = 80,
  KeyQ = 81,
  KeyR = 82,
  KeyS = 83,
  KeyT = 84,
  KeyU = 85,
  KeyV = 86,
  KeyW = 87,
  KeyX = 88,
  KeyY = 89,
  KeyZ = 90,
  LeftBracket = 91,
  Backslash = 92,
  RightBracket = 93,
  GraveAccent = 96,
  World1 = 161,
  World2 = 162,
  Escape = 256,
  Enter = 257,
  Tab = 258,
  Backspace = 259,
  Insert = 260,
  Delete = 261,
  KeyRight = 262,
  KeyLeft = 263,
  KeyDown = 264,
  KeyUp = 265,
  PageUp = 266,
  PageDown = 267,
  KeyHome = 268,
  KeyEnd = 269,
  KeyCapsLock = 280,
  KeyScrollLock = 281,
  KeyNumLock = 282,
  KeyPrintScreen = 283,
  KeyPause = 284,
  KeyF1 = 290,
  KeyF2 = 291,
  KeyF3 = 292,
  KeyF4 = 293,
  KeyF5 = 294,
  KeyF6 = 295,
  KeyF7 = 296,
  KeyF8 = 297,
  KeyF9 = 298,
  KeyF10 = 299,
  KeyF11 = 300,
  KeyF12 = 301,
  KeyF13 = 302,
  KeyF14 = 303,
  KeyF15 = 304,
  KeyF16 = 305,
  KeyF17 = 306,
  KeyF18 = 307,
  KeyF19 = 308,
  KeyF20 = 209,
  KeyF21 = 310,
  KeyF22 = 311,
  KeyF23 = 312,
  KeyF24 = 313,
  KeyF25 = 314,
  KeyPad0 = 320,
  KeyPad1 = 321,
  KeyPad2 = 322,
  KeyPad3 = 323,
  KeyPad4 = 324,
  KeyPad5 = 325,
  KeyPad6 = 326,
  KeyPad7 = 327,
  KeyPad8 = 328,
  KeyPad9 = 329,
  KeyPadDecimal = 330,
  KeyPadDivide = 331,
  KeyPadMultiply = 332,
  KeyPadSubtract = 333,
  KeyPadAdd = 334,
  KeyPadEnter = 335,
  KeyPadEqual = 336,
  LeftShift = 340,
  LeftControl = 341,
  LeftAlt = 342,
  LeftSuper = 343,
  RightShift = 344,
  RightControl = 345,
  RightAlt = 346,
  RightSuper = 347,
  KeyMenu = 348
} Key;

typedef enum KeyAction {
  Release = 0,
  Press = 1,
  Repeat = 2
} KeyAction;

typedef struct RenderInfo RenderInfo;

#define LOWEST_KEY 32
#define HIGHEST_KEY 348

typedef void(* KeyCallbackFunction)(RenderInfo *, int);
typedef void(* ClickCallbackFunction)(RenderInfo *, int, int, int);
typedef struct InputInfo {
  Key *chars;
  KeyAction *actions;
  KeyCallbackFunction *callbacks;

  int callbacks_n;

  int keystates[HIGHEST_KEY];

  ClickCallbackFunction clickCallback;
} InputInfo;

typedef GLuint ShaderProgram;
typedef void(* WindowResizeCallback)(RenderInfo *, int, int);
typedef struct RenderInfo {
  GLFWwindow *window;

  // Shaders
  ShaderProgram shader3D;
  ShaderProgram shader2D;
  ShaderProgram shader2DTextured;

  TextRenderInfo textRenderer;

  Camera camera;

  Model sphere;
  Model cube;

  Shape quad2D; // The quad used for 2D rendering
  Menu menu;

  WindowResizeCallback resizeCallback;

  InputInfo input;
} RenderInfo;

RenderInfo * createRenderer(GLFWwindow *window);
Camera * getCamera(RenderInfo *renderer);
void freeRenderer(RenderInfo *renderer);

void beginRender(RenderInfo *renderer);
void endRender(RenderInfo *renderer);

void renderSphere(RenderInfo *renderer, float radius, Vector3 color, Vector3 position);
void renderQuad(RenderInfo *renderer, Vector2 size, Vector2 position, Vector4 color, double z);
void renderText(RenderInfo *renderer, const char *text, Vector2 position, Vector4 color, double z);
void renderMenu(RenderInfo *renderer, Menu *menu);
void renderOrientation(RenderInfo *renderer);
void renderGrid(RenderInfo *renderer);

Vector2 getWindowSize(const RenderInfo *renderer);
Vector2 getCursorPosition(const RenderInfo *renderer);
int isLeftMouseButtonPressed(const RenderInfo *renderer);
void clear(GLFWwindow *window);
void swapBuffers(GLFWwindow *window);
void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha);

void addKeyCallback(RenderInfo *renderer, Key key, KeyAction action, KeyCallbackFunction callback);
void setResizeCallback(RenderInfo *renderer, WindowResizeCallback callback);
void setClickCallback(RenderInfo *renderer, ClickCallbackFunction callback);

#endif
