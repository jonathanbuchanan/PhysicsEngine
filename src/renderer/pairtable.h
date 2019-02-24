  #ifndef PAIR_TABLE_H
  #define PAIR_TABLE_H

  typedef enum BreakOpportunity {
    Prohibited,
    Indirect,
    ProhibitedCM,
    IndirectCM,
    Direct
  } BreakOpportunity;

  #define PAIR_TABLE_SIZE 29
  static const BreakOpportunity pairTable[PAIR_TABLE_SIZE][PAIR_TABLE_SIZE] = {

    {Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, ProhibitedCM, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, Prohibited, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Prohibited, IndirectCM, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Prohibited, IndirectCM, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Direct, Indirect, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Indirect, Indirect, Indirect, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Indirect, Indirect, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Indirect, Indirect, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Direct, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Direct, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Prohibited, IndirectCM, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Direct, Prohibited, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Indirect, Indirect, Indirect, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, },
    {Indirect, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, Prohibited, IndirectCM, Prohibited, Indirect, Indirect, Indirect, Indirect, Indirect, Indirect, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Indirect, Indirect, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Indirect, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Indirect, Indirect, Indirect, Indirect, Direct, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Indirect, Indirect, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Indirect, Direct, Direct, Direct, Direct, Indirect, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Indirect, Direct, },
    {Direct, Prohibited, Prohibited, Indirect, Indirect, Indirect, Prohibited, Prohibited, Prohibited, Direct, Direct, Direct, Direct, Direct, Direct, Direct, Indirect, Indirect, Direct, Direct, Prohibited, IndirectCM, Prohibited, Direct, Direct, Direct, Direct, Direct, Indirect, },
  };

  #endif

