#include "menu.h"

#include "render.h"
#include <stdlib.h>

int drawControl(Control *control, RenderInfo *renderer, Vector2 offset) {
  return (control->draw)(control->control, renderer, offset);
}

int updateControl(Control *control, RenderInfo *renderer) {
  return (control->update)(control->control, renderer);
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
  // Draw the background
  renderQuad(renderer, menu->size, menu->position, menu->color);

  for (int i = 0; i < menu->controls_n; ++i) {
    drawControl(menu->controls[i], renderer, menu->position);
  }
  return 0;
}

int updateMenu(Menu *menu, RenderInfo *renderer) {
  for (int i = 0; i < menu->controls_n; ++i) {
    updateControl(menu->controls[i], renderer);
  }
  return 0;
}



Control createButton(Vector2 size, Vector2 position) {
  Button *b = malloc(sizeof(Button));

  b->state = Normal;
  b->size = size;
  b->position = position;

  Control c = {b, drawButton, updateButton};

  return c;
}

int drawButton(void *c, RenderInfo *renderer, Vector2 offset) {
  Button *button = (Button *)c;

  Vector4 color;
  if (button->state == Normal)
    color = button->color;
  else if (button->state == Highlighted)
    color = button->highlight;
  else if (button->state == Selected)
    color = button->select; 
  
  renderQuad(renderer, button->size, addVector2(button->position, offset), color);
  renderText(renderer, button->text, addVector2(button->position, offset), button->textColor);

  return 0;
}

int updateButton(void *c, RenderInfo *renderer) {
  Button *button = (Button *)c;

  Vector2 cursorPosition = getCursorPosition(renderer);
  int leftButton = isLeftMouseButtonPressed(renderer);

  // Test for mouse position
  if (cursorPosition.x >= button->position.x && cursorPosition.y >= button->position.y &&
      cursorPosition.x <= button->position.x + button->size.x && cursorPosition.y <= button->position.y + button->size.y) {
    if (leftButton == 1) {
      // Call the action if the state changed to selected
      if (button->state != Selected && button->action != NULL)
        button->action(button);
      button->state = Selected;
    } else
      button->state = Highlighted;
  } else {
    button->state = Normal;
  }

  return 0;
}

Button * getButton(Control *button) {
  return (Button *)button->control;
}



Control createLabel(Vector2 size, Vector2 position) {
  Label *l = malloc(sizeof(Label));

  l->size = size;
  l->position = position;

  Control c = {l, drawLabel, updateLabel};

  return c;
}

int drawLabel(void *c, RenderInfo *renderer, Vector2 offset) {
  Label *label = (Label *)c;

  renderText(renderer, label->text, addVector2(label->position, offset), label->color);

  return 0;
}

int updateLabel(void *c, RenderInfo *renderer) {
  Label *label = (Label *)c;
  return 0;
}

Label * getLabel(Control *label) {
  return (Label *)label->control;
}
