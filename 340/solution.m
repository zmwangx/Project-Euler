S[a_, b_, c_] := Block[{q = Quotient[b, a], r = Mod[b, a]},
   (b (b + 1))/
    2 + (2 q^2 + 2 q) a^2 - (3 q^2 + 5 q)/
     2 a c + (r + 1) ((4 q + 4) a - (3 q + 4) c)];
Print[S[21^7, 7^21, 12^7]~Mod~(10^9)];
