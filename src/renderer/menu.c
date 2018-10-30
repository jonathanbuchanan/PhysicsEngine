#include "menu.h"

#include "render.h"
#include "text.h"
#include <stdlib.h>

int drawControl(Control *control, RenderInfo *renderer) {
  return (control->draw)(control->control, renderer);
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
  for (int i = 0; i < menu->controls_n; ++i) {
    drawControl(menu->controls[i], renderer);
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

int drawButton(void *c, RenderInfo *renderer) {
  Button *button = (Button *)c;

  Vector2 windowSize = getWindowSize(renderer);

  // Convert pixel coordinates to NDC
  // Position specifies bottom left coordinates
  Vector2 size = (Vector2){2 * (button->size.x / windowSize.x), 2 * (button->size.y / windowSize.y)};
  Vector2 position = (Vector2){(2 * (button->position.x / windowSize.x)) - 1.0 + (size.x / 2), (2 * (button->position.y / windowSize.y)) - 1.0 + (size.y / 2)};

  Vector4 color;
  if (button->state == Normal)
    color = button->color;
  else if (button->state == Highlighted)
    color = button->highlight;
  else if (button->state == Selected)
    color = button->select; 
  
  renderQuad(renderer, size, position, color);
  drawText(renderer, button->text, position, size, 1, button->textColor);

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

int drawLabel(void *c, RenderInfo *renderer) {
  Label *label = (Label *)c;

  Vector2 windowSize = getWindowSize(renderer);

  // Convert pixel coordinates to NDC
  // Position specifies bottom left coordinates
  Vector2 size = (Vector2){2 * (label->size.x / windowSize.x), 2 * (label->size.y / windowSize.y)};
  Vector2 position = (Vector2){(2 * (label->position.x / windowSize.x)) - 1.0 + (size.x / 2), (2 * (label->position.y / windowSize.y)) - 1.0 + (size.y / 2)};

  drawText(renderer, label->text, label->position, label->size, 1, label->color);
  //renderText(renderer, label->text, label->position, label->color);

  return 0;
}

int updateLabel(void *c, RenderInfo *renderer) {
  Label *label = (Label *)c;
  return 0;
}

Label * getLabel(Control *label) {
  return (Label *)label->control;
}
