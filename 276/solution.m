a[n_] := Round[If[EvenQ[n], n^2, (n + 3)^2]/48];
b[n_] := DivisorSum[n, a[#] MoebiusMu[n/#] &];
Print[Total[b /@ Range[10000000]]];
