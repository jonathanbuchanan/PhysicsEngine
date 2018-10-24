#ifndef TEXT_H
#define TEXT_H

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

#endif
