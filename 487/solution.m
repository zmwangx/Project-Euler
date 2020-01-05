kk = 10^4;
nn = 10^12;
primes = Prime /@ Range[PrimePi[2 10^9] + 1, PrimePi[2 10^9 + 2000]];
B[i_] := B[i] = BernoulliB[i];
coeff[k_, i_] := ((-1)^(k + 2 - i)/((k + 1) (k + 2))
    Sum[Multinomial[i, j, k + 2 - i - j] B[j] B[k + 2 - i - j],
     {j, 0, Min[k, k + 2 - i]}]);
poly[k_] := poly[k] = Parallelize[Table[coeff[k, i], {i, k + 2}]];
rationalMod[r_, p_] := 
  Mod[Numerator[r] ModularInverse[Denominator[r], p], p];
polyMod[k_, n_, p_] := 
  Fold[Mod[n (#1 + rationalMod[#2, p]), p] &, 0, Reverse[poly[k]]];
Print[polyMod[kk, nn, #] & /@ primes // Total];
