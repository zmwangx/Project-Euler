F[n_, x_, mod_] := 
 Block[{denom = x^2 + x - 1, M = mod (x^2 + x - 1), fn, fn1, xn1},
  {fn, fn1} = Algebra`MatrixPowerMod[{{0, 1}, {1, 1}}, n, M].{0, 1};
  xn1 = PowerMod[x, n + 1, M];
  Mod[(fn xn1 x + fn1 xn1 - x)/denom, mod]];
Print[Mod[Total[F[10^15, #, 15!] & /@ Range[100]], 15!]];
