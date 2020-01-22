#!/usr/bin/env wolframscript
reducedExp3[n_, mod_] := Block[{phi = EulerPhi[mod], doubleExp, exp},
   doubleExp = PowerMod[3, n - 2, phi] - 3; 
   exp = If[OddQ[phi], 
     If[EvenQ[doubleExp], doubleExp/2, (doubleExp + phi)/2],
     If[EvenQ[doubleExp/2], doubleExp/2, (doubleExp + phi)/2]];
   exp + phi];
reducedExp2[n_, mod_] := 
  Block[{phi = EulerPhi[mod]}, PowerMod[3, n - 2, phi] + phi];
Cmod[n_, mod_] := 
  Mod[PowerMod[3, reducedExp3[n, mod], mod] PowerMod[2, 
     reducedExp2[n, mod], mod], mod];

mod1 = 13^8;
mod2 = EulerPhi[mod1];
mod3 = EulerPhi[mod2];
(* C(10000) *)
r3 = Cmod[10000, mod3];
(* C(C(10000)) *)
r2 = Cmod[r3 + mod3, mod2];
(* C(C(C(10000))) *)
r1 = Cmod[r2 + mod2, mod1];
Print[r1];
