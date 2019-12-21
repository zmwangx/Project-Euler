L[n_] := Block[{r = n/2^IntegerExponent[n, 2]/5^IntegerExponent[n, 5]},
   If[r == 1, 0, MultiplicativeOrder[10, r]]];
Print[Total[L /@ Range[3, 10^8] // Parallelize]];
