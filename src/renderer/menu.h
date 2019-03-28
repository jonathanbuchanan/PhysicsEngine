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

#define Z_INDEX_MAX 127



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
  unsigned int z_index;

  Vector4 color;

  Control **controls;
  int controls_n;
} Menu;

Menu * createMenu();
int drawMenu(Menu *menu, RenderInfo *renderer);
int updateMenu(Menu *menu, RenderInfo *renderer);
void addControlToMenu(Menu *menu, Control *control);
void setMenuOrientation(Menu *menu, MenuOrientation orientation);
void setMenuPosition(Menu *menu, Vector2 position);
void setMenuSize(Menu *menu, Vector2 size);
void setMenuColor(Menu *menu, Vector4 color);

// Menu Controls (sizes are given in pixels)
typedef struct Button {
  ControlState state;

  Vector2 size;
  Vector2 position;
  unsigned int z_index;

  Vector4 color;
  Vector4 highlight;
  Vector4 select;

  Vector4 textColor;
  int textHeight;

  const char *text;

  void (* action)(struct Button *sender);
} Button;

Control * createButton();
int drawButton(void *c, RenderInfo *renderer, Vector2 offset);
int updateButton(void *c, RenderInfo *renderer);
Button * getButton(Control *button);
void setButtonZ(Control *button, unsigned int z);
void setButtonPosition(Control *button, Vector2 position);
void setButtonSize(Control *button, Vector2 size);
void setButtonColor(Control *button, Vector4 color);
void setButtonText(Control *button, char * text);
void setButtonTextHeight(Control *button, int textHeight);
void setButtonTextColor(Control *button, Vector4 color);
void setButtonAction(Control *button, void (* action)(struct Button *));

typedef struct Label {
  Vector2 size;
  Vector2 position;
  unsigned int z_index;

  Vector4 color;
  int textHeight;

  const char *text;
} Label;

Control * createLabel();
int drawLabel(void *c, RenderInfo *renderer, Vector2 offset);
int updateLabel(void *c, RenderInfo *renderer);
Label * getLabel(Control *label);
void setLabelZ(Control *label, unsigned int z);
void setLabelPosition(Control *label, Vector2 position);
void setLabelSize(Control *label, Vector2 size);
void setLabelColor(Control *label, Vector4 color);
void setLabelText(Control *label, char * text);
void setLabelTextHeight(Control *label, int textHeight);

#endif
