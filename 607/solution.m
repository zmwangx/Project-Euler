SetOptions[$Output, FormatType->OutputForm];
CotCos[x_] := x/Sqrt[1 - x^2]; SecCos[x_] := 1/Sqrt[1 - x^2]; 
XOffset[x_] := 50*(Sqrt[2] - 1)*CotCos[x] + 10*(CotCos[(9*x)/10] + CotCos[(8*x)/10] + 
      CotCos[(7*x)/10] + CotCos[(6*x)/10] + CotCos[(5*x)/10]); 
Time[x_] := (50/10)*(Sqrt[2] - 1)*SecCos[x] + 
    10*((1/9)*SecCos[(9*x)/10] + (1/8)*SecCos[(8*x)/10] + (1/7)*SecCos[(7*x)/10] + 
      (1/6)*SecCos[(6*x)/10] + (1/5)*SecCos[(5*x)/10]); 
Print[NumberForm[Time[x] /. FindRoot[XOffset[x] - 50*Sqrt[2], {x, 1/Sqrt[2]}, 
     AccuracyGoal -> 20, PrecisionGoal -> 20, WorkingPrecision -> 40], {12, 10}]]
