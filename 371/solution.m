SetOptions[$Output, FormatType->OutputForm];
transitionMatrix[n_] := SparseArray[Flatten[Table[{
       {2 k + 1, 2 k + 1} -> (k + 1)/(2 n),
       {2 k + 1, 2 k + 2} -> 1/(2 n),
       {2 k + 1, 2 k + 3} -> 1 - (k + 1)/n,
       {2 k + 1, 2 n + 2} -> k/(2 n),
       {2 k + 2, 2 k + 2} -> (k + 1)/(2 n),
       {2 k + 2, 2 k + 4} -> 1 - (k + 1)/n,
       {2 k + 2, 2 n + 2} -> (k + 1)/(2 n)
       }, {k, 0, n - 1}]]~Join~{{2 n + 2, 2 n + 2} -> 1}, {2 n + 2, 
    2 n + 2}];
terms[n_, m_] := 
  Block[{v = UnitVector[2 n + 2, 1], t = transitionMatrix[n]},
   Differences[#[[2 n + 2]] & /@ 
      FoldList[Dot, v, ConstantArray[t, m]]] Range[m]];
Print[NumberForm[N[Total[terms[500, 250]]], {10, 8}]];
