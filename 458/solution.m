stateCounts = 7 UnitVector[7, 1]. Algebra`MatrixPowerMod[{
      {1, 6, 0, 0, 0, 0, 0},
      {1, 1, 5, 0, 0, 0, 0},
      {1, 1, 1, 4, 0, 0, 0},
      {1, 1, 1, 1, 3, 0, 0},
      {1, 1, 1, 1, 1, 2, 0},
      {1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 7}
      }, 10^12 - 1, 10^9];
Print[Mod[Total[Drop[stateCounts, -1]], 10^9]];
