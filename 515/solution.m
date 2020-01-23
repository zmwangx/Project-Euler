#!/usr/bin/env wolframscript
d[a_, b_, k_] := Sum[ModularInverse[k - 1, Prime[i]],
   {i, PrimePi[a - 1] + 1, PrimePi[a + b - 1]}];
Print[d[10^9, 10^5, 10^5]];
