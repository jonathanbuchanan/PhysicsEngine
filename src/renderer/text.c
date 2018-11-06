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

  error = FT_Set_Pixel_Sizes(textRenderer.face, 0, FONT_SIZE);
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

#define CHAR_RANGE(char_, a, b) (char_ >= a && char_ <= b)

#define RANGE_BREAK_CLASS_IF(char_, a, b, class) \
  if CHAR_RANGE(char_, a, b) {\
    return class;\
  }

#define RANGE_BREAK_CLASS_ELIF(char_, a, b, class) \
  else if CHAR_RANGE(char_, a, b) {\
    return class;\
  }

LineBreakClass getLineBreakClass(int c) {
  RANGE_BREAK_CLASS_IF(c, 0x00, 0x08, CM)
  RANGE_BREAK_CLASS_ELIF(c, 0x09, 0x09, BA)
  RANGE_BREAK_CLASS_ELIF(c, 0x0A, 0x0A, LF)
  RANGE_BREAK_CLASS_ELIF(c, 0x0B, 0x0C, BK)
  RANGE_BREAK_CLASS_ELIF(c, 0x0D, 0x0D, CR)
  RANGE_BREAK_CLASS_ELIF(c, 0x0E, 0x1F, CM)
  RANGE_BREAK_CLASS_ELIF(c, 0x20, 0x20, SP)
  RANGE_BREAK_CLASS_ELIF(c, 0x21, 0x21, EX)
  RANGE_BREAK_CLASS_ELIF(c, 0x22, 0x22, QU)
  RANGE_BREAK_CLASS_ELIF(c, 0x23, 0x23, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x24, 0x24, PR)
  RANGE_BREAK_CLASS_ELIF(c, 0x25, 0x25, PO)
  RANGE_BREAK_CLASS_ELIF(c, 0x26, 0x26, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x27, 0x27, QU)
  RANGE_BREAK_CLASS_ELIF(c, 0x28, 0x28, OP)
  RANGE_BREAK_CLASS_ELIF(c, 0x29, 0x29, CP)
  RANGE_BREAK_CLASS_ELIF(c, 0x2A, 0x2A, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x2B, 0x2B, PR)
  RANGE_BREAK_CLASS_ELIF(c, 0x2C, 0x2C, IS)
  RANGE_BREAK_CLASS_ELIF(c, 0x2D, 0x2D, HY)
  RANGE_BREAK_CLASS_ELIF(c, 0x2E, 0x2E, IS)
  RANGE_BREAK_CLASS_ELIF(c, 0x2F, 0x2F, SY)
  RANGE_BREAK_CLASS_ELIF(c, 0x30, 0x39, NU) // Digits
  RANGE_BREAK_CLASS_ELIF(c, 0x3A, 0x3B, IS)
  RANGE_BREAK_CLASS_ELIF(c, 0x3C, 0x3E, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x3F, 0x3F, EX)
  RANGE_BREAK_CLASS_ELIF(c, 0x40, 0x40, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x41, 0x5A, AL) // Latin capital letters
  RANGE_BREAK_CLASS_ELIF(c, 0x5B, 0x5B, OP)
  RANGE_BREAK_CLASS_ELIF(c, 0x5C, 0x5C, PR)
  RANGE_BREAK_CLASS_ELIF(c, 0x5D, 0x5D, CP)
  RANGE_BREAK_CLASS_ELIF(c, 0x5E, 0x5E, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x5F, 0x5F, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x60, 0x60, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x61, 0x7A, AL) // Latin lowercase letters
  RANGE_BREAK_CLASS_ELIF(c, 0x7B, 0x7B, OP)
  RANGE_BREAK_CLASS_ELIF(c, 0x7C, 0x7C, BA)
  RANGE_BREAK_CLASS_ELIF(c, 0x7D, 0x7D, CL)
  RANGE_BREAK_CLASS_ELIF(c, 0x7E, 0x7E, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0x7F, 0x7F, CM)
  RANGE_BREAK_CLASS_ELIF(c, 0x80, 0x84, CM)
  RANGE_BREAK_CLASS_ELIF(c, 0x85, 0x85, NL)
  RANGE_BREAK_CLASS_ELIF(c, 0x86, 0x9F, CM)
  RANGE_BREAK_CLASS_ELIF(c, 0xA0, 0xA0, GL)
  RANGE_BREAK_CLASS_ELIF(c, 0xA1, 0xA1, OP)
  RANGE_BREAK_CLASS_ELIF(c, 0xA2, 0xA2, PO)
  RANGE_BREAK_CLASS_ELIF(c, 0xA3, 0xA5, PR)
  RANGE_BREAK_CLASS_ELIF(c, 0xA6, 0xA6, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xA7, 0xA7, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xA8, 0xA8, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xA9, 0xA9, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xAA, 0xAA, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xAB, 0xAB, QU)
  RANGE_BREAK_CLASS_ELIF(c, 0xAC, 0xAC, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xAD, 0xAD, BA)
  RANGE_BREAK_CLASS_ELIF(c, 0xAE, 0xAE, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xAF, 0xAF, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xB0, 0xB0, PO)
  RANGE_BREAK_CLASS_ELIF(c, 0xB1, 0xB1, PR)
  RANGE_BREAK_CLASS_ELIF(c, 0xB2, 0xB3, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xB4, 0xB4, BB)
  RANGE_BREAK_CLASS_ELIF(c, 0xB5, 0xB5, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xB6, 0xB7, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xB8, 0xB8, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xB9, 0xB9, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xBA, 0xBA, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xBB, 0XBB, QU)
  RANGE_BREAK_CLASS_ELIF(c, 0xBC, 0xBE, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xBF, 0xBF, OP)
  RANGE_BREAK_CLASS_ELIF(c, 0xC0, 0xD6, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xD7, 0xD7, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xD8, 0xF6, AL)
  RANGE_BREAK_CLASS_ELIF(c, 0xF7, 0xF7, AI)
  RANGE_BREAK_CLASS_ELIF(c, 0xF8, 0xFF, AL)
  // Expand!
  // https://www.unicode.org/Public/UCD/latest/ucd/LineBreak.txt
  return XX;
}

int lineBreaks(const char *text) {
  // LB1
  unsigned int length = strlen(text);
  LineBreakClass *lineBreakClasses = malloc(sizeof(LineBreakClass) * length);
  OpportunityType *opportunities = malloc(sizeof(OpportunityType) * (length + 1));
  memset(opportunities, 0, (length + 1) * sizeof(OpportunityType));
  for (int i = 0; i < length; ++i) {
    LineBreakClass class = getLineBreakClass(text[i]);
    // Resolve certain classes
    if (class == AI || class == SG || class == XX)
      class = AL;
    else if (class == SA)
      class = CM;
    else if (class == CB) // this might be wrong. it probably is
      class = AL;
    else if (class == CJ)
      class = NS;
    lineBreakClasses[i] = class;
  }

  // LB2
  opportunities[0] = Unallowed;

  // LB3
  opportunities[length] = Mandatory;

  // LB4
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == BK)
      opportunities[i + 1] = Mandatory;
  }

  // LB5
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == CR)
      opportunities[i + 1] = Mandatory;
    else if (lineBreakClasses[i] == LF)
      opportunities[i + 1] = Mandatory;
    else if (lineBreakClasses[i] == NL)
      opportunities[i + 1] = Mandatory;


    if (i != length - 1) { // Can there be a 'next' character?
      if (lineBreakClasses[i] == CR && lineBreakClasses[i + 1] == LF) {
        opportunities[i + 1] = Unallowed;
        opportunities[i + 2] = Mandatory;
      }
    }
  }

  // LB6
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == BK || lineBreakClasses[i] == CR || lineBreakClasses[i] == LF || lineBreakClasses[i] == NL)
      opportunities[i] = Unallowed;
  }

  // LB7
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == SP || lineBreakClasses[i] == ZW)
      opportunities[i] = Unallowed;
  }

  // LB8
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == ZW) {
      int breakpoint = i + 1;
      while (lineBreakClasses[breakpoint] == SP || breakpoint < length) {
        opportunities[breakpoint] = Permitted; // <--- check this again
        ++breakpoint;
      }
    }
  }

  // LB9
  // LB10

  // LB11
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == WJ) {
      opportunities[i] = Unallowed;
      opportunities[i + 1] = Unallowed;
    }
  }

  // LB12
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == GL)
      opportunities[i + 1] = Unallowed;
  }

  // LB12a
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] != SP && lineBreakClasses[i] != BA && lineBreakClasses[i] != HY && i + 1 < length) {
      if (lineBreakClasses[i + 1] == GL)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB13
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == CL || lineBreakClasses[i] == CP || lineBreakClasses[i] == EX || lineBreakClasses[i] == IS || lineBreakClasses[i] == SY)
      opportunities[i] = Unallowed;
  }

  // LB14
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == OP) {
      int breakpoint = i + 1;
      while (lineBreakClasses[breakpoint] == SP || breakpoint < length) {
        opportunities[breakpoint] = Unallowed; //
        ++breakpoint;
      }
    }
  }

  // LB15
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == QU) {
      // Search for OP
      int ruleActive = 0;
      int location = i + 1;
      while (lineBreakClasses[location] == SP && location < length) {
        if (location + 1 < length && lineBreakClasses[location] == OP) {
          ruleActive = 1;
          break;
        }
        ++location;
      }

      if (ruleActive) {
        location = i + 1;
        while (lineBreakClasses[location] == SP && location < length) {
          opportunities[location + 1] = Unallowed;
          if (location + 1 < length && lineBreakClasses[location] == OP)
            break;
          ++location;
        }
      }
    }
  }

  // LB16
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == CL || lineBreakClasses[i] == CP) {
      int ruleActive = 0;
      int location = i + 1;
      while (lineBreakClasses[location] == SP && location < length) {
        if (location + 1 < length && lineBreakClasses[location] == NS) {
          ruleActive = 1;
          break;
        }
        ++location;
      }

      if (ruleActive) {
        location = i + 1;
        while (lineBreakClasses[location] == SP && location < length) {
          opportunities[location + 1] = Unallowed;
          if (location + 1 < length && lineBreakClasses[location] == NS)
            break;
          ++location;
        }
      }
    }
  }

  // LB17
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == B2) {
      int ruleActive = 0;
      int location = i + 1;
      while (lineBreakClasses[location] == SP && location < length) {
        if (location + 1 < length && lineBreakClasses[location] == B2) {
          ruleActive = 1;
          break;
        }
        ++location;
      }
      // What if no spaces? look at 15 and 16

      if (ruleActive) {
        location = i + 1;
        while (lineBreakClasses[location] == SP && location < length) {
          opportunities[location + 1] = Unallowed;
          if (location + 1 < length && lineBreakClasses[location] == B2)
            break;
          ++location;
        }
      }
    }
  }

  // LB18
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == SP)
      opportunities[i + 1] = Permitted;
  }

  // LB19
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == QU) {
      opportunities[i] = Unallowed;
      opportunities[i + 1] = Unallowed;
    }
  }

  // LB20
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == CB) {
      opportunities[i] = Permitted;
      opportunities[i + 1] = Permitted;
    }
  }

  // LB21
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == BA || lineBreakClasses[i] == HY || lineBreakClasses[i] == NS)
      opportunities[i] = Unallowed;
    else if (lineBreakClasses[i] == BB)
      opportunities[i + 1] = Unallowed;
  }

  // LB21a
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == HL) {
      if (i + 1 < length && (lineBreakClasses[i + 1] == HY || lineBreakClasses[i + 1] == BA))
        opportunities[i + 2] = Unallowed;
    }
  }

  // LB21b
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == SY) {
      if (i + 1 < length && lineBreakClasses[i + 1] == HL)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB22
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == AL || lineBreakClasses[i] == HL || lineBreakClasses[i] == EX || lineBreakClasses[i] == ID || lineBreakClasses[i] == EB || lineBreakClasses[i] == EM || lineBreakClasses[i] == IN || lineBreakClasses[i] == NU) {
      if (i + 1 < length && lineBreakClasses[i + 1] == IN)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB23
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == AL || lineBreakClasses[i] == HL) {
      if (i + 1 < length && lineBreakClasses[i + 1] == NU)
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == NU) {
      if (i + 1 < length && (lineBreakClasses[i + 1] == AL || lineBreakClasses[i + 1] == HL))
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB23a
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == PR) {
      if (i + 1 < length && (lineBreakClasses[i + 1] == ID || lineBreakClasses[i + 1] == EB || lineBreakClasses[i + 1] == EM))
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == ID || lineBreakClasses[i] == EB || lineBreakClasses[i] == EM) {
      if (i + 1 < length && lineBreakClasses[i + 1] == PO)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB24
  for (int i = 0; i < length; ++i) {
    if (lineBreakClasses[i] == PR || lineBreakClasses[i] == PO) {
      if (i + 1 < length && (lineBreakClasses[i + 1] == AL || lineBreakClasses[i + 1] == HL))
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == AL || lineBreakClasses[i] == HL) {
      if (i + 1 < length && (lineBreakClasses[i + 1] == PR || lineBreakClasses[i + 1] == PO))
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB25
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if ((lineBreakClasses[i] == CL && lineBreakClasses[i + 1] == PO) ||
        (lineBreakClasses[i] == CP && lineBreakClasses[i + 1] == PO) ||
        (lineBreakClasses[i] == CL && lineBreakClasses[i + 1] == PR) ||
        (lineBreakClasses[i] == CP && lineBreakClasses[i + 1] == PR) ||
        (lineBreakClasses[i] == NU && lineBreakClasses[i + 1] == PO) ||
        (lineBreakClasses[i] == NU && lineBreakClasses[i + 1] == PR) ||
        (lineBreakClasses[i] == PO && lineBreakClasses[i + 1] == OP) ||
        (lineBreakClasses[i] == PO && lineBreakClasses[i + 1] == NU) ||
        (lineBreakClasses[i] == PR && lineBreakClasses[i + 1] == OP) ||
        (lineBreakClasses[i] == PR && lineBreakClasses[i + 1] == NU) ||
        (lineBreakClasses[i] == HY && lineBreakClasses[i + 1] == NU) ||
        (lineBreakClasses[i] == IS && lineBreakClasses[i + 1] == NU) ||
        (lineBreakClasses[i] == NU && lineBreakClasses[i + 1] == NU) ||
        (lineBreakClasses[i] == SY && lineBreakClasses[i + 1] == NU))
      opportunities[i + 1] = Unallowed;
  }

  // LB26
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == JL) {
      if (lineBreakClasses[i + 1] == JL || lineBreakClasses[i + 1] == JV || lineBreakClasses[i + 1] == H2 || lineBreakClasses[i + 1] == H3)
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == JV || lineBreakClasses[i] == H2) {
      if (lineBreakClasses[i + 1] == JV || lineBreakClasses[i + 1] == JT)
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == JT || lineBreakClasses[i] == H3) {
      if (lineBreakClasses[i + 1] == JT)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB27
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == JL || lineBreakClasses[i] == JV || lineBreakClasses[i] == JT || lineBreakClasses[i] == H2 || lineBreakClasses[i] == H3) {
      if (lineBreakClasses[i + 1] == IN || lineBreakClasses[i + 1] == PO)
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == PR) {
      if (lineBreakClasses[i + 1] == JL || lineBreakClasses[i + 1] == JV || lineBreakClasses[i + 1] == JT || lineBreakClasses[i + 1] == H2 || lineBreakClasses[i + 1] == H3)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB28
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == AL || lineBreakClasses[i] == HL) {
      if (lineBreakClasses[i + 1] == AL || lineBreakClasses[i + 1] == HL)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB29
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == IS) {
      if (lineBreakClasses[i + 1] == AL || lineBreakClasses[i + 1] == HL)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB30
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == AL || lineBreakClasses[i] == HL || lineBreakClasses[i] == NU) {
      if (lineBreakClasses[i + 1] == OP)
        opportunities[i + 1] = Unallowed;
    } else if (lineBreakClasses[i] == CP) {
      if (lineBreakClasses[i + 1] == AL || lineBreakClasses[i + 1] == HL || lineBreakClasses[i + 1] == NU)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB30a
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == RI && lineBreakClasses[i + 1] == RI) {
      int location = i - 1;
      int ricount = 0;
      while (location >= 0 && lineBreakClasses[location] == RI) {
        ++ricount;
        --location;
      }
      if (ricount % 2 == 0)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB30b
  for (int i = 0; i < length; ++i) {
    if (i + 1 >= length)
      continue;
    if (lineBreakClasses[i] == EB) {
      if (lineBreakClasses[i + 1] == EM)
        opportunities[i + 1] = Unallowed;
    }
  }

  // LB31

  printf("break action: %d\n", opportunities[0]);
  for (int i = 0; i < length; ++i) {
    printf("break action: %c %d\n", text[i], opportunities[i + 1]);
  }

  return 0;
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

    pos.x += (textRenderer->glyphs[c].advance * scale) / 64;
  }
}
