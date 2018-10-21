#ifndef MENU_H
#define MENU_H

typedef struct RenderInfo RenderInfo;

#include "vector.h"

typedef struct Control {
  void *control;
  int (* draw)(void *control, RenderInfo *renderer);
  int (* update)(void *control);
} Control;

int drawControl(Control *control, RenderInfo *renderer);
int updateControl(Control *control);

typedef struct Menu {
  Control **controls;
  int controls_n;
} Menu;

Menu createMenu();
int drawMenu(Menu *menu, RenderInfo *renderer);
int updateMenu(Menu *menu);
void addControlToMenu(Menu *menu, Control *control);

// Menu Controls (sizes are given in pixels)
typedef struct Button {
  Vector2 size;
  Vector2 position;

  Vector4 color;
  Vector4 highlight;
  Vector4 textColor;

  const char *text;

  void (* action)(struct Button *sender);
} Button;

Control createButton(Vector2 size, Vector2 position);
int drawButton(void *c, RenderInfo *renderer);
int updateButton(void *c);

typedef struct Label {
  Vector2 size;
  Vector2 position;

  Vector4 color;

  const char *text;
} Label;

Control createLabel();
int drawLabel(void *c, RenderInfo *renderer);
int updateLabel(void *c);

#endif
