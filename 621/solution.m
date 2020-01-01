G[n_] := Table[
    SquaresR[2, 8 n + 3 - k^2]/4, {k, 1, Sqrt[8 n + 3], 2}] // 
   Parallelize // Total;
Print[G[17526 10^9]];
