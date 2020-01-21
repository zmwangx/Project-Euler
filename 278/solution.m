#!/usr/bin/env wolframscript
p[i_] := p[i] = Prime[i];
g[p_, q_, r_] := 2 p q r - p q - q r - r p;
n = PrimePi[5000];
Print[Parallelize[
   Sum[g[p[i], p[j], p[k]], {i, 1, n}, {j, i + 1, n}, {k, j + 1, 
     n}]]];
