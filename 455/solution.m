f[n_] := If[Mod[n, 10] == 0, 0, 
   FixedPoint[PowerMod[n, #, 10^9] &, 1]];
Print[Total[f /@ Range[2, 10^6]]];
