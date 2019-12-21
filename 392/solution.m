SetOptions[$Output, FormatType->OutputForm];
m[n_] := NumberForm[
   NMinimize[{
      4 (Sin[Subscript[t, 1]] + 
         Sum[Sin[Subscript[t, i + 1]] Cos[Subscript[t, i]], {i, 1, 
           n - 1}] + Cos[Subscript[t, n]] - 
         Sum[Sin[Subscript[t, i]] Cos[Subscript[t, i]], {i, 1, n}]),
      AllTrue[{{Subscript[t, 1], 0}, 
        Sequence @@ 
         Table[{Subscript[t, i + 1], Subscript[t, i]}, {i, 1, 
           n - 1}], {Pi/2, Subscript[t, n]}}, #[[1]] >= #[[2]] &]
      },
     Table[Subscript[t, i], {i, 1, n}],
     Method -> {"Automatic", 
       "InitialPoints" -> {Table[i Pi/(2 (n + 1)), {i, 1, n}]}}
     ][[1]], {11, 10}];
Print[m[200]];
