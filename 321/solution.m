f[n_] := FullSimplify[((1 + Sqrt[8]) (3 + Sqrt[8])^
       n - (1 - Sqrt[8]) (3 - Sqrt[8])^n)/(2 Sqrt[8])];
g[n_] := FullSimplify[((-1 + Sqrt[8]) (3 + Sqrt[8])^
       n - (-1 - Sqrt[8]) (3 - Sqrt[8])^n)/(2 Sqrt[8])];
n = 40;
Take[(f /@ Range[n])~Join~(g /@ Range[n]) // Sort, n] - 1 // 
  Total // Print
