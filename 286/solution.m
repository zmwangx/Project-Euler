SetOptions[$Output, FormatType->OutputForm];
p[q_] := Coefficient[Expand[Product[(1 - i/q) x + i/q, {i, 50}]], 
  x^20];
Print[NumberForm[
  q /. FindRoot[p[q] == 1/50, {q, 50}, AccuracyGoal -> 10,
    PrecisionGoal -> 10, WorkingPrecision -> 20], {12, 10}]]
