SetOptions[$Output, FormatType->OutputForm];
Off[Power::infy];
Off[Infinity::indet];
Off[NIntegrate::nlim];
Off[NIntegrate::ncvb];
V[R_, x_, a_] := Tan[a] (Pi R^2 (R + x) - 1/3 Pi (R + x)^3 +
     NIntegrate[
      r^2 ArcCos[(R^2 - x^2 - r^2)/(2 x r)] -
       R^2 ArcCos[(R^2 + x^2 - r^2)/(2 x R)] +
       1/2 Sqrt[(x + r + R) (x + r - R) (x + R - r) (r + R - x)], {r,
       R - x, R + x}, PrecisionGoal -> 15]);
R = 6;
a = 40 Degree;
Vmin = V[R, 0, a];
Vmax = V[R, 6, a];
range = Range[Ceiling[Sqrt[Vmin]], Floor[Sqrt[Vmax]]];
sum = Re[x] /.
      FindRoot[V[R, x, a] == #^2, {x, 0.1},
       WorkingPrecision -> 20] & /@ range // Total;
Print[NumberForm[sum, {Infinity, 9}]];
