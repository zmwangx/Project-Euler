T[m_] := SparseArray[
   (Table[{i, i + 1}, {i, m - 1}]~Join~{{m, 1}, {m, 2}})
    -> ConstantArray[1, m + 1],
   {m, m}];
g[m_, k_, mod_] := Mod[
   Algebra`MatrixPowerMod[T[m] // Normal, k, mod][[1]].ConstantArray[
     1, m], mod];
Print[g[2000, 10^18, 20092010]];
