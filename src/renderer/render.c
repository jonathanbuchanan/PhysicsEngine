#include "render.h"
#include "vector.h"
#include "model.h"

#include <stdlib.h>
#include <stdio.h>

static const char *vertex_shader_3D =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 color;\n"
"void main() {\n"
"    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
"    color = pos;\n"
"}\n";

static const char *fragment_shader_3D =
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4((color / 2) + vec3(0.5, 0.5, 0.5), 1.0);\n"
"}\n";



static const char *vertex_shader_2D =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform float zPosition;\n"
"void main() {\n"
"    gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
"    gl_Position.z = -zPosition;\n"
"}\n";

static const char *fragment_shader_2D =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 color;\n"
"void main() {\n"
"    FragColor = color;\n"
"}\n";



static const char *vertex_shader_2D_textured =
"#version 330 core\n"
"layout (location = 0) in vec2 pos;\n"
"layout (location = 1) in vec2 textureCoordinates;\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform float zPosition;\n"
"out vec2 texCoords;\n"
"void main() {\n"
"    gl_Position = projection * model * vec4(pos, 0.0, 1.0);\n"
"    gl_Position.z = -zPosition;\n"
"    texCoords = textureCoordinates;\n"
"}\n";

static const char *fragment_shader_2D_textured =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 texCoords;\n"
"uniform sampler2D text;\n"
"uniform vec4 color;\n"
"void main() {\n"
"    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);\n"
"    FragColor = color * sampled;\n"
"}\n";



ShaderProgram compileShader(const char *vertex_shader_source, const char *fragment_shader_source) {
  GLuint vertex_shader, fragment_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);

  glCompileShader(vertex_shader);
  glCompileShader(fragment_shader);

  int success;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Vertex shader error\n");
    return -1;
  }
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Fragment shader error\n");
    return -1;
  }

  ShaderProgram program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  return program;
}

int loadFont(RenderInfo *renderer) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  int error = FT_Init_FreeType(&renderer->fontLibrary);
  if (error)
    return -1;

  error = FT_New_Face(renderer->fontLibrary, "/Library/Fonts/Arial.ttf", 0, &renderer->fontFace);
  if (error)
    return -1;

  error = FT_Set_Pixel_Sizes(renderer->fontFace, 0, 48);
  if (error)
    return -1;

  for (int c = 0; c < GLYPH_COUNT; ++c) {
    error = FT_Load_Char(renderer->fontFace, c, FT_LOAD_RENDER);
    if (error)
      return -1;

    Glyph g;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, renderer->fontFace->glyph->bitmap.width, renderer->fontFace->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, renderer->fontFace->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    g.textureID = texture;
    g.size = vec2(renderer->fontFace->glyph->bitmap.width, renderer->fontFace->glyph->bitmap.rows);
    g.bearing = vec2(renderer->fontFace->glyph->bitmap_left, renderer->fontFace->glyph->bitmap_top);
    g.advance = renderer->fontFace->glyph->advance.x;

    renderer->glyphs[c] = g;
  }

  return 0;
}

void test_callback(Button *b) {
  printf("press\n");
}

void checkKeys(RenderInfo *renderer) {
  for (int i = 0; i < renderer->input.callbacks_n; ++i) {
    int key = renderer->input.chars[i];
    int action = renderer->input.actions[i];
    int previousState = renderer->input.keystates[key];
    int state = glfwGetKey(renderer->window, key);
    if (previousState == 0 && state == 1 && action == Press) renderer->input.callbacks[i](renderer, key);
    if (previousState == 1 && state == 0 && action == Release) renderer->input.callbacks[i](renderer, key);
    if (previousState == 1 && state == 1 && action == Repeat) renderer->input.callbacks[i](renderer, key);
  }
  for (int i = LOWEST_KEY; i < HIGHEST_KEY; ++i) {
    renderer->input.keystates[i] = glfwGetKey(renderer->window, i);
  }
}

void windowResizeCallback(GLFWwindow *window, int width, int height) {
  // Resize menus
}

Control button;
Control label;
RenderInfo * createRenderer(GLFWwindow *window) {
  glfwMakeContextCurrent(window);

  glfwSetWindowSizeCallback(window, windowResizeCallback);

  RenderInfo *renderer = malloc(sizeof(RenderInfo));

  renderer->input.chars = NULL;
  renderer->input.actions = NULL;
  renderer->input.callbacks = NULL;

  glfwSetWindowUserPointer(window, renderer);

  if (loadFont(renderer) == -1)
    return NULL;

  renderer->window = window;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  GLuint vao;
  glGenVertexArrays(1, &vao);

  ShaderProgram shader3D = compileShader(vertex_shader_3D, fragment_shader_3D);
  if (shader3D == -1) {
    printf("Error compiling 3D shader\n");
  } else {
    renderer->shader3D = shader3D;
  }

  ShaderProgram shader2D = compileShader(vertex_shader_2D, fragment_shader_2D);
  if (shader2D == -1) {
    printf("Error compiling 2D shader\n");
  } else {
    renderer->shader2D = shader2D;
  }

  ShaderProgram shader2DTextured = compileShader(vertex_shader_2D_textured, fragment_shader_2D_textured);
  if (shader2DTextured == -1) {
    printf("Error compiling 2D-Textured shader\n");
  } else {
    renderer->shader2DTextured = shader2DTextured;
  }

  renderer->camera.position = vec3(0.0, 0.0, -10.0);
  renderer->camera.target = vec3(0.0, 0.0, 0.0);
  renderer->camera.up = vec3(0.0, 1.0, 0.0);

  //renderer->model = generateIcoSphere(1.0, 1);
  renderer->model = generateCube(1.0);
  loadModel(&renderer->model);

  renderer->quad2D = generateQuad();
  loadShape(&renderer->quad2D);

  renderer->menu = createMenu();
  renderer->menu.position = vec2(0.0, 0.0);
  renderer->menu.size = vec2(100.0, 480.0);
  renderer->menu.color = vec4(0.8, 0.8, 0.8, 0.5);

  button = createButton(vec2(100.0, 100.0), vec2(0.0, 0.0));
  Button *b = getButton(&button);
  b->highlight = vec4(1.0, 1.0, 1.0, 1.0);
  b->select = vec4(1.0, 0.0, 1.0, 1.0);
  b->action = test_callback;
  b->text = "Button";
  b->textColor = vec4(0.5, 0.5, 0.5, 1.0);
  b->z_index = 1;
  addControlToMenu(&renderer->menu, &button);

  label = createLabel(vec2(100.0, 100.0), vec2(0.0, 100.0));
  Label *l = getLabel(&label);
  l->color = vec4(1.0, 1.0, 1.0, 1.0);
  l->text = "I am a label.";
  l->z_index = 1;
  addControlToMenu(&renderer->menu, &label);

  return renderer;
}

Camera * getCamera(RenderInfo *renderer) {
  return &renderer->camera;
}

void freeRenderer(RenderInfo *renderer) {
  freeModel(&renderer->model);
  freeShape(&renderer->quad2D);

  FT_Done_Face(renderer->fontFace);
  FT_Done_FreeType(renderer->fontLibrary);
}

double step = 0.0;
void render(RenderInfo *renderer) {
  GLFWwindow *window = renderer->window;

  glfwMakeContextCurrent(window);

  checkKeys(renderer);

  // Set the viewport
  int height, width;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Clear
  clear(window);

  // Draw
  glUseProgram(renderer->shader3D);

  renderer->model.position = vec3(0.0, 2.0 * sin(step), 0.0);
  renderer->model.eulerRotation = vec3(step, 0.5 * step, 2.0 * step);
  //step += 0.01;
  Matrix4x4F model = matrix4x4toMatrix4x4F(modelMatrix(&renderer->model));
  unsigned int modelL = glGetUniformLocation(renderer->shader3D, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  Matrix4x4F view = matrix4x4toMatrix4x4F(getViewMatrix(&renderer->camera));
  unsigned int viewL = glGetUniformLocation(renderer->shader3D, "view");
  glUniformMatrix4fv(viewL, 1, GL_TRUE, (GLfloat *)&view.a11);

  Matrix4x4F projection = matrix4x4toMatrix4x4F(perspectiveProjectionMatrix(0.1, 100.0, DEGREES_TO_RADIANS(45.0), (double)(width) / (double)(height)));
  unsigned int projectionL = glGetUniformLocation(renderer->shader3D, "projection");
  glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

  drawModel(&renderer->model);



  ((Button *)button.control)->color = vec4(fabs(sin(step * 0.4)), fabs(cos(step * 0.2)), fabs(sin(step * 0.55)), 1.0);

  glUseProgram(renderer->shader2D);

  updateMenu(&renderer->menu, renderer);
  drawMenu(&renderer->menu, renderer);

  // Swap the buffers
  swapBuffers(window);
  glfwPollEvents();
}

void renderQuad(RenderInfo *renderer, Vector2 size, Vector2 position, Vector4 color, double z) {
  glUseProgram(renderer->shader2D);

  renderer->quad2D.size = size;
  renderer->quad2D.position = position;

  Vector2 windowSize = getWindowSize(renderer);

  Matrix4x4F model = matrix4x4toMatrix4x4F(shapeModelMatrix(&renderer->quad2D));
  unsigned int modelL = glGetUniformLocation(renderer->shader2D, "model");
  glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

  Matrix4x4F projection = matrix4x4toMatrix4x4F(orthographicProjectionMatrix(-1.0, 1.0, 0.0, windowSize.x, 0.0, windowSize.y));
  unsigned int projectionL = glGetUniformLocation(renderer->shader2D, "projection");
  glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

  unsigned int zPositionL = glGetUniformLocation(renderer->shader2D, "zPosition");
  glUniform1f(zPositionL, z);

  unsigned int colorL = glGetUniformLocation(renderer->shader2D, "color");
  glUniform4f(colorL, color.x, color.y, color.z, color.w);

  drawShape(&renderer->quad2D);
}

void renderText(RenderInfo *renderer, const char *text, Vector2 position, Vector4 color, double z) {
  float scale = 1;

  glUseProgram(renderer->shader2DTextured);

  Vector2 pos = position;

  Vector2 windowSize = getWindowSize(renderer);

  for (int i = 0; i < strlen(text); ++i) {
    char c = text[i];
    Glyph *g = &renderer->glyphs[c];

    Vector2 characterPos;
    characterPos.x = pos.x + (renderer->glyphs[c].bearing.x * scale);
    characterPos.y = pos.y - ((renderer->glyphs[c].size.y - renderer->glyphs[c].bearing.y) * scale);

    Vector2 characterSize;
    characterSize = vec2(renderer->glyphs[c].size.x * scale, renderer->glyphs[c].size.y * scale);

    renderer->quad2D.size = characterSize;
    renderer->quad2D.position = characterPos;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g->textureID);

    Matrix4x4F model = matrix4x4toMatrix4x4F(shapeModelMatrix(&renderer->quad2D));
    unsigned int modelL = glGetUniformLocation(renderer->shader2DTextured, "model");
    glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

    Matrix4x4F projection = matrix4x4toMatrix4x4F(orthographicProjectionMatrix(-1.0, 1.0, 0.0, windowSize.x, 0.0, windowSize.y));
    unsigned int projectionL = glGetUniformLocation(renderer->shader2DTextured, "projection");
    glUniformMatrix4fv(projectionL, 1, GL_TRUE, (GLfloat *)&projection.a11);

    unsigned int colorL = glGetUniformLocation(renderer->shader2DTextured, "color");
    glUniform4f(colorL, color.x, color.y, color.z, color.w);

    unsigned int zPositionL = glGetUniformLocation(renderer->shader2DTextured, "zPosition");
    glUniform1f(zPositionL, z);

    drawShape(&renderer->quad2D);

    pos.x += renderer->glyphs[c].advance / 64;
  }
}

Vector2 getWindowSize(const RenderInfo *renderer) {
  int width, height;
  glfwGetWindowSize(renderer->window, &width, &height);
  return (Vector2){(double)width, (double)height};
}

Vector2 getCursorPosition(const RenderInfo *renderer) {
  Vector2 size = getWindowSize(renderer);

  double x, y;
  glfwGetCursorPos(renderer->window, &x, &y);
  return vec2(x, size.y - y);
}

int isLeftMouseButtonPressed(const RenderInfo *renderer) {
  int state = glfwGetMouseButton(renderer->window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS)
    return 1;
  else
    return 0;
}

void clear(GLFWwindow *window) {
  glfwMakeContextCurrent(window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swapBuffers(GLFWwindow *window) {
  glfwSwapBuffers(window);
}

void setClearColor(GLFWwindow *window, float red, float green, float blue, float alpha) {
  glfwMakeContextCurrent(window);
  glClearColor(red, green, blue, alpha);
}

void addKeyCallback(RenderInfo *renderer, Key key, KeyAction action, KeyCallbackFunction callback) {
  renderer->input.callbacks_n += 1;

  renderer->input.chars = realloc(renderer->input.chars, renderer->input.callbacks_n * sizeof(Key));
  renderer->input.actions = realloc(renderer->input.actions, renderer->input.callbacks_n * sizeof(KeyAction));
  renderer->input.callbacks = realloc(renderer->input.callbacks, renderer->input.callbacks_n * sizeof(KeyCallbackFunction));

  renderer->input.chars[renderer->input.callbacks_n - 1] = key;
  renderer->input.actions[renderer->input.callbacks_n - 1] = action;
  renderer->input.callbacks[renderer->input.callbacks_n - 1] = callback;
}
