firstHalf[l_] := Take[l, Ceiling[Length[l]/2]];
smallDivisors[n_] := firstHalf[Divisors[n]];
alexandrians[pmax_] :=
  Flatten[Table[
    p (p + #) (p + (p^2 + 1)/#) & /@ smallDivisors[p^2 + 1], {p,
     pmax}]];
Print[RankedMax[alexandrians[150000], -150000]];
