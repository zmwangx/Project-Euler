count = 10^5;
starting = 10^14;
pi[x_] := x/Log[x];
xmax = Round[
    x /. FindRoot[pi[x] == pi[starting] + count, {x, starting}]] + 
   count;
primes = Select[Range[starting + 1, xmax, 2], PrimeQ, count];
matrixPowerMod[a_, n_, m_] :=
  Fold[Mod[If[#2 == 1, a.#, #].#, m] &, a, Rest[IntegerDigits[n, 2]]];
modulus = 1234567891011;
Print[Total[
    matrixPowerMod[{{0, 1}, {1, 1}}, #, modulus][[1, 2]] & /@ primes]~
   Mod~modulus];
