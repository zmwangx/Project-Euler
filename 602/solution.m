#!/usr/bin/env wolframscript
nn = 10^7;
kk = 4 10^6;
modulus = 10^9 + 7;

factmod = FoldList[Mod[#1 #2, modulus] &, Range[nn + 1]];
factinvmod = ParallelMap[ModularInverse[#, modulus] &, factmod];
factorialMod[n_] := If[n == 0, 1, Part[factmod, n]];
factorialInvMod[n_] := If[n == 0, 1, Part[factinvmod, n]];

binomialMod[n_, k_] := 
  Mod[factorialMod[n] factorialInvMod[k] factorialInvMod[n - k], 
   modulus];

eulerianMod[n_, k_] := 
  Mod[Parallelize[
    Sum[(-1)^i binomialMod[n + 1, i] PowerMod[k + 1 - i, n, 
       modulus], {i, 0, k}]], modulus];
c[n_, k_] := eulerianMod[n, n - k];

Print[c[nn, kk]];
