#ifndef TEXT_H
#define TEXT_H

#include "vector.h"
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// The font height in pixels
#define FONT_SIZE 64

// The number of glyphs loaded
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
  SY, // Symbols Allowing Break After

  AI, // Ambiguous
  AL, // Alphabetic
  CJ, // Conditional Japanese Starter
  EB, // Emoji Base
  EM, // Emoji modifier
  H2, // Hangul LV Symbol
  H3, // Hangul LVT Symbol
  HL, // Hebrew Letter
  ID, // Ideographic
  JL, // Hangul L Jamo
  JV, // Hangul V Jamo
  JT, // Hangul T Jamo
  RI, // Regional Indicator
  SA, // Complex Context Dependent (South East Asian)
  XX  // Unknown  
} LineBreakClass;

/*typedef enum LineBreakOpportunityType {
  Prohibited,
  Indirect,
  ProhibitedForCombiningMarks,
  IndirectForCombinbingMarksFollowingSpace,
  Direct
} LineBreakOpportunityType;

#define PRD_BO Prohibited
#define IDT_BO Indirect
#define PCM_BO ProhibitedForCombiningMarks
#define ICM_BO IndirectForCombiningMarksFollowingSpace
#define DCT_BO Direct

// Pair Table Index
#define PAIR_TABLE_SIZE 29
static const LineBreakClass pairTableIndex[] = {
  OP,
  CL,
  CP,
  QU,
  GL,
  NS,
  EX,
  SY,
  IS,
  PR,
  PO,
  NU,
  AL,
  HL,
  ID,
  IN,
  HY,
  BA,
  BB,
  B2,
  ZW,
  CM,
  WJ,
  H2,
  H3,
  JL,
  JV,
  JT,
  RI
};*/

#include "pairtable.h"

void drawText(RenderInfo *renderer, const char *text, Vector2 position, Vector2 size, float scale, Vector4 color);

#endif
