S[n_, mod_] := Block[{q = Quotient[n, 9], r = Mod[n, 9]},
   ((((r + 1) (r + 2))/2 + 5) PowerMod[10, q, mod] - (9 q + r + 6))~
    Mod~mod];
p = 1000000007;
Print[Total[S[Fibonacci[#] & /@ Range[2, 90], p]]~Mod~p];
