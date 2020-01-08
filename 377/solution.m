t = SparseArray[{
      Table[{i, 1} -> 10, {i, 1, 9}],
      Table[{i, 1} -> i - 9, {i, 10, 18}],
      Table[{i, 10} -> 1, {i, 10, 18}],
      Table[{i - 1, i} -> 1, {i, 2, 9}],
      Table[{i - 1, i} -> 1, {i, 11, 18}
       ]} // Flatten] // Normal;
v = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
mod = 10^9;
f[n_] := Mod[First[v.Algebra`MatrixPowerMod[t, n, mod]], mod];
Print[Mod[Sum[f[13^i], {i, 1, 17}], mod]];
