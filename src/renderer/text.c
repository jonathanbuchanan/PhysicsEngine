#include "text.h"

#include "render.h"

TextRenderInfo initTextRenderer() {
  TextRenderInfo textRenderer;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  

  int error = FT_Init_FreeType(&textRenderer.library);
  /*if (error)
    return -1;*/

  error = FT_New_Face(textRenderer.library, "/Library/Fonts/Arial.ttf", 0, &textRenderer.face);
  /*if (error)
    return -1;*/

  error = FT_Set_Pixel_Sizes(textRenderer.face, 0, 48);
  /*if (error)
    return -1;*/

  for (int c = 0; c < GLYPH_COUNT; ++c) {
    error = FT_Load_Char(textRenderer.face, c, FT_LOAD_RENDER);
    /*if (error)
      return -1;*/

    Glyph g;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, textRenderer.face->glyph->bitmap.width, textRenderer.face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, textRenderer.face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    g.textureID = texture;
    g.size = vec2(textRenderer.face->glyph->bitmap.width, textRenderer.face->glyph->bitmap.rows);
    g.bearing = vec2(textRenderer.face->glyph->bitmap_left, textRenderer.face->glyph->bitmap_top);
    g.advance = textRenderer.face->glyph->advance.x;

    textRenderer.glyphs[c] = g;
  }

  return textRenderer;
}

void destroyTextRenderer(TextRenderInfo *textRenderer) {
  FT_Done_Face(textRenderer->face);
  FT_Done_FreeType(textRenderer->library);
}

void drawText(RenderInfo *renderer, const char *text, Vector2 position, Vector2 size, float scale, Vector4 color) {
  TextRenderInfo *textRenderer = &renderer->textRenderer;

  glUseProgram(renderer->shader2DTextured);

  Vector2 pos = position;

  Vector2 windowSize = getWindowSize(renderer);

  for (int i = 0; i < strlen(text); ++i) {
    char c = text[i];
    Glyph *g = &textRenderer->glyphs[c];

    Vector2 characterPos;
    characterPos.x = pos.x + (textRenderer->glyphs[c].bearing.x * scale);
    characterPos.y = pos.y - ((textRenderer->glyphs[c].size.y - textRenderer->glyphs[c].bearing.y) * scale);

    Vector2 characterSize;
    characterSize = vec2(textRenderer->glyphs[c].size.x * scale, textRenderer->glyphs[c].size.y * scale);

    renderer->quad2D.size = vec2(2 * (characterSize.x / windowSize.x), 2 * (characterSize.y / windowSize.y));
    renderer->quad2D.position = vec2((2 * (characterPos.x / windowSize.x)) - 1.0 + (renderer->quad2D.size.x / 2), (2 * (characterPos.y / windowSize.y)) - 1.0 + (renderer->quad2D.size.y / 2));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g->textureID);

    Matrix4x4F model = matrix4x4toMatrix4x4F(shapeModelMatrix(&renderer->quad2D));
    unsigned int modelL = glGetUniformLocation(renderer->shader2DTextured, "model");
    glUniformMatrix4fv(modelL, 1, GL_TRUE, (GLfloat *)&model.a11);

    unsigned int colorL = glGetUniformLocation(renderer->shader2DTextured, "color");
    glUniform4f(colorL, color.x, color.y, color.z, color.w);

    drawShape(&renderer->quad2D);

    pos.x += textRenderer->glyphs[c].advance / 64;
  }
}
