F[n2_, n1_, n0_] := 
  If[n2 == 0, 2^n1 (n0 + 3), 2^# # &@F[n2 - 1, n1, n0]];
Fmod[n_, m_] := Fmod2[n - 1, n, m];
Fmod2[n_, k_, m_] := 
  Fmod2[n, k, m] = 
   If[n == 0, Mod[PowerMod[2, k, m] k, m], 
    Mod[PowerMod[2, Fmod2[n - 1, k, EulerPhi[m]] + EulerPhi[m], 
       m] Fmod2[n - 1, k, m], m]];

Print[Mod[Total[Join[(F[##] - 3) & @@@ Tuples[{0, 1}, 3],
    (Block[{$RecursionLimit = Infinity}, Fmod[F[##], 10^9]] - 3) & @@@
      Tuples[{0, 1}, 3]]], 10^9]];
