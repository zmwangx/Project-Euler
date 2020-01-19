#!/usr/bin/env wolframscript
SetOptions[$Output, FormatType -> OutputForm];
q[k_] := q[k] = 
   Sum[(-1)^(i - k)/i!*Binomial[k - 1, i - 1]*x^i, {i, 1, k}];
count[i_] := 
  count[i] = 
   Binomial[13, i] Integrate[
     Exp[-x] q[4]^i (3 q[3] + 3 q[2] + q[1])^(13 - i), {x, 0, 
      Infinity}];
total = 52!/(4!)^13;
Print[NumberForm[
   Sum[i count[i], {i, 0, 13}]/total // N, {Infinity, 10}]];
Print[NumberForm[
   Total[count /@ {2, 3, 5, 7, 11, 13}]/total // N, {Infinity, 10}]];
