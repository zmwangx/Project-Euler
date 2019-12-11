f[n_] := (x*(n-1)/(2*n) - ArcSin[x]/2 + 1/(2*n) /. {x -> (Sqrt[2*n^3] - n + 1)/(n^2 + 1)}) / (1 - Pi/4);
n = 1; While[f[n] >= 0.001, n++]; Print[n]
