#include "menu.h"

#include "render.h"
#include <stdlib.h>

int drawControl(Control *control, RenderInfo *renderer) {
  return (control->draw)(control->control, renderer);
}

int updateControl(Control *control) {
  return (control->update)(control->control);
}



Menu createMenu() {
  Menu m = (Menu){};
  return m;
}

void addControlToMenu(Menu *menu, Control *control) {
  menu->controls = realloc(menu->controls, sizeof(Control *) * menu->controls_n);
  menu->controls[menu->controls_n] = control;
  ++menu->controls_n;
}

int drawMenu(Menu *menu, RenderInfo *renderer) {
  for (int i = 0; i < menu->controls_n; ++i) {
    drawControl(menu->controls[i], renderer);
  }
  return 0;
}

int updateMenu(Menu *menu) {
  for (int i = 0; i < menu->controls_n; ++i) {
    updateControl(menu->controls[i]);
  }
  return 0;
}



Control createButton(Vector2 size, Vector2 position) {
  Button *b = malloc(sizeof(Button));

  b->size = size;
  b->position = position;

  Control c = {b, drawButton, updateButton};

  return c;
}

int drawButton(void *c, RenderInfo *renderer) {
  Button *button = (Button *)c;

  // Convert pixel coordinates to NDC
  // Position specifies bottom left coordinates
  Vector2 windowSize = getWindowSize(renderer);
  Vector2 size = (Vector2){2 * (button->size.x / windowSize.x), 2 * (button->size.y / windowSize.y)};
  Vector2 position = (Vector2){(2 * (button->position.x / windowSize.x)) - 1.0 + (size.x / 2), (2 * (button->position.y / windowSize.y)) - 1.0 + (size.y / 2)};
  
  renderQuad(renderer, size, position, button->color);

  return 0;
}

int updateButton(void *c) {
  Button *button = (Button *)c;
  return 0;
}



Control createLabel() {
  Label *l = malloc(sizeof(Label));

  Control c = {l, drawLabel, updateLabel};

  return c;
}

int drawLabel(void *c, RenderInfo *renderer) {
  Label *label = (Label *)c;
  return 0;
}

int updateLabel(void *c) {
  Label *label = (Label *)c;
  return 0;
}
