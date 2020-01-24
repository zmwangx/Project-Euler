#!/usr/bin/env wolframscript
SetOptions[$Output, FormatType->OutputForm];

x[a_, b_, t_] :=
  a EllipticE[t, 1 - b^2/a^2] +
   Sqrt[a^2 Sin[t]^2 + b^2 Cos[t]^2] Cos[
     ArcTan[a Tan[t]/b] + ArcTan[a Cot[t]/b]];
y[a_, b_, t_] :=
  Sqrt[a^2 Sin[t]^2 + b^2 Cos[t]^2] Sin[
    ArcTan[a Tan[t]/b] + ArcTan[a Cot[t]/b]];

(*c[a_,b_]:=ParametricPlot[{x[a,b,t],y[a,b,t]},{t,0,Pi/2},AxesOrigin\
\[Rule]{0,0},GridLines\[Rule]Automatic];*)

curveLength[a_, b_] :=
  4 NIntegrate[
    Sqrt[D[x[a, b, t], t]^2 + D[y[a, b, t], t]^2], {t, 0, Pi/2}];
Print[NumberForm[
   curveLength[1, 4] + curveLength[3, 4], {Infinity, 8}]];
