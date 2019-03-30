#include "menu.h"

#include "render.h"
#include "text.h"
#include <stdlib.h>

int drawControl(Control *control, RenderInfo *renderer, Vector2 offset) {
  return (control->draw)(control->control, renderer, offset);
}

int updateControl(Control *control, RenderInfo *renderer) {
  return (control->update)(control->control, renderer);
}


Menu * createMenu() {
  Menu *menu = malloc(sizeof(Menu));

  menu->controls = NULL;
  menu->orientation = Vertical;
  menu->position = vec2(0.0, 0.0);
  menu->size = vec2(0.0, 0.0);
  menu->color = vec4(0.0, 0.0, 0.0, 0.0);
  menu->z_index = 0;
  menu->controls_n = 0;

  return menu;
}

void addControlToMenu(Menu *menu, Control *control) {
  menu->controls = realloc(menu->controls, sizeof(Control *) * (menu->controls_n + 1));
  menu->controls[menu->controls_n] = control;
  ++menu->controls_n;
}

void setMenuOrientation(Menu *menu, MenuOrientation orientation) {
  menu->orientation = orientation;
}

void setMenuPosition(Menu *menu, Vector2 position) {
  menu->position = position;
}

void setMenuSize(Menu *menu, Vector2 size) {
  menu->size = size;
}

void setMenuColor(Menu *menu, Vector4 color) {
  menu->color = color;
}

int drawMenu(Menu *menu, RenderInfo *renderer) {
  // Draw the background
  renderQuad(renderer, menu->size, menu->position, menu->color, menu->z_index / Z_INDEX_MAX);

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

Control * createButton() {
  Button *b = malloc(sizeof(Button));

  b->state = Normal;

  Control *c = malloc(sizeof(Control));
  c->control = b;
  c->draw = drawButton;
  c->update = updateButton;

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

  renderQuad(renderer, button->size, button->position, color, button->z_index / Z_INDEX_MAX);
  drawText(renderer, button->text, button->position, button->size, (float)button->textHeight / (float)FONT_SIZE, button->textColor);

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

void setButtonZ(Control *button, unsigned int z) {
  getButton(button)->z_index = z;
}

void setButtonPosition(Control *button, Vector2 position) {
  getButton(button)->position = position;
}

void setButtonSize(Control *button, Vector2 size) {
  getButton(button)->size = size;
}

void setButtonColor(Control *button, Vector4 color) {
  getButton(button)->color = color;
}

void setButtonText(Control *button, char * text) {
  getButton(button)->text = text;
}

void setButtonTextHeight(Control *button, int textHeight) {
  getButton(button)->textHeight = textHeight;
}

void setButtonTextColor(Control *button, Vector4 color) {
  getButton(button)->textColor = color;
}

void setButtonAction(Control *button, void (* action)(struct Button *)) {
  getButton(button)->action = action;
}


Control * createLabel() {
  Label *l = malloc(sizeof(Label));

  Control *c = malloc(sizeof(Control));
  c->control = l;
  c->draw = drawLabel;
  c->update = updateLabel;

  return c;
}

int drawLabel(void *c, RenderInfo *renderer, Vector2 offset) {
  Label *label = (Label *)c;

  Vector2 windowSize = getWindowSize(renderer);

  // Convert pixel coordinates to NDC
  // Position specifies bottom left coordinates
  drawText(renderer, label->text, add2(label->position, offset), label->size, (float)label->textHeight / (float)FONT_SIZE, label->color);

  return 0;
}

int updateLabel(void *c, RenderInfo *renderer) {
  Label *label = (Label *)c;
  return 0;
}

Label * getLabel(Control *label) {
  return (Label *)label->control;
}

void setLabelZ(Control *label, unsigned int z) {
  getLabel(label)->z_index = z;
}

void setLabelPosition(Control *label, Vector2 position) {
  getLabel(label)->position = position;
}

void setLabelSize(Control *label, Vector2 size) {
  getLabel(label)->size = size;
}

void setLabelColor(Control *label, Vector4 color) {
  getLabel(label)->color = color;
}

void setLabelText(Control *label, char * text) {
  getLabel(label)->text = text;
}

void setLabelTextHeight(Control *label, int textHeight) {
  getLabel(label)->textHeight = textHeight;
}
