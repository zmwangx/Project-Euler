#!/usr/bin/env wolframscript
SetOptions[$Output, FormatType->OutputForm];
index = ToExpression[$ScriptCommandLine[[2]]];
last16 = Algebra`MatrixPowerMod[{{1, 1}, {1, 0}}, index, 10^16][[1, 2]];
approximation = FortranForm[N[GoldenRatio^index/Sqrt[5], 2]];
Print[last16, ",", approximation];
