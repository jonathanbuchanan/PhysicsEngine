#ifndef MENU_H
#define MENU_H

typedef struct RenderInfo RenderInfo;

#include "vector.h"

typedef enum ControlState {
  Normal = 0,
  Highlighted = 1,
  Selected = 2
} ControlState;

typedef enum MenuOrientation {
  Vertical = 0,
  Horizontal = 1,
  Central = 2
} MenuOrientation;

typedef struct Control {
  void *control;
  int (* draw)(void *control, RenderInfo *renderer, Vector2 offset);
  int (* update)(void *control, RenderInfo *renderer);
} Control;

int drawControl(Control *control, RenderInfo *renderer, Vector2 offset);
int updateControl(Control *control, RenderInfo *renderer);

typedef struct Menu {
  MenuOrientation orientation;
  Vector2 size;
  Vector2 position;
  Vector4 color;

  Control **controls;
  int controls_n;
} Menu;

Menu createMenu();
int drawMenu(Menu *menu, RenderInfo *renderer);
int updateMenu(Menu *menu, RenderInfo *renderer);
void addControlToMenu(Menu *menu, Control *control);

// Menu Controls (sizes are given in pixels)
typedef struct Button {
  ControlState state;

  Vector2 size;
  Vector2 position;

  Vector4 color;
  Vector4 highlight;
  Vector4 select;

  Vector4 textColor;

  const char *text;

  void (* action)(struct Button *sender);
} Button;

Control createButton(Vector2 size, Vector2 position);
int drawButton(void *c, RenderInfo *renderer, Vector2 offset);
int updateButton(void *c, RenderInfo *renderer);
Button * getButton(Control *button);

typedef struct Label {
  Vector2 size;
  Vector2 position;

  Vector4 color;

  const char *text;
} Label;

Control createLabel(Vector2 size, Vector2 position);
int drawLabel(void *c, RenderInfo *renderer, Vector2 offset);
int updateLabel(void *c, RenderInfo *renderer);
Label * getLabel(Control *label);

#endif
