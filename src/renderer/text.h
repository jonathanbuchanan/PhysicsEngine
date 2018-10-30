#ifndef TEXT_H
#define TEXT_H

#include "vector.h"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define GLYPH_COUNT 128

typedef struct RenderInfo RenderInfo;

typedef struct Glyph {
  GLuint textureID;
  Vector2 size;
  Vector2 bearing;
  double advance;
} Glyph;

typedef struct TextRenderInfo {
  FT_Library library;
  FT_Face face;
  Glyph glyphs[GLYPH_COUNT];
} TextRenderInfo;

TextRenderInfo initTextRenderer();
void destroyTextRenderer(TextRenderInfo *textRenderer);

// This is an implementation of the Unicode Line Breaking Algorithm

typedef enum LineBreakClass {
  BK, // Mandatory Break
  CR, // Carriage Return
  LF, // Line Feed
  CM, // Combining Mark
  NL, // Next Line
  SG, // Surrogate
  WJ, // Word Joiner
  ZW, // Zero Width Space
  GL, // Non-breaking ("Glue")
  SP, // Space
  ZWJ, // Zero Width Joiner

  B2, // Break Opportunity Before and After
  BA, // Break After
  BB, // Break Before
  HY, // Hyphen
  CB, // Contingent Break Opportunity

  CL, // Close Punctuation
  CP, // Close Parenthesis
  EX, // Exclamation/Interrogation
  IN, // Inseparable
  NS, // Nonstarter
  OP, // Open Punctuation
  QU, // Quotation

  IS, // Infix Numeric Separator
  NU, // Numeric
  PO, // Postfix Numeric
  PR, // Prefix Numeric
  SY  // Symbols Allowing Break After
} LineBreakClass;

void drawText(RenderInfo *renderer, const char *text, Vector2 position, Vector2 size, float scale, Vector4 color);

#endif
