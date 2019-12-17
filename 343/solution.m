gpf[n_] := FactorInteger[n][[-1, 1]];
(Max[gpf[# + 1], gpf[#^2 - # + 1]] - 1) & /@ Range[2000000] // Total // Print;
