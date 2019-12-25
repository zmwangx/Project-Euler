S[n_] := If[n <= 3, PrimePi[n], 
   PrimePi[n] + PrimePi[n - 2] + (Ceiling[n/2] - 1) (Floor[n/2] - 2)];
Print[Sum[S[Fibonacci[k]], {k, 3, 44}]];
