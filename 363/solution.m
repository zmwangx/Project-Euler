SetOptions[$Output, FormatType->OutputForm];
p0 = {1, 0}; p1 = {1, v}; p2 = {v, 1}; p3 = {0, 1};
q0 = (1 - t) p0 + t p1;
q1 = (1 - t) p1 + t p2;
q2 = (1 - t) p2 + t p3;
r0 = (1 - t) q0 + t q1;
r1 = (1 - t) q1 + t q2;
b = (1 - t) r0 + t r1;
{x, y} = b;
area = -Integrate[D[x, t] y, {t, 0, 1}];
sol = Solve[area == Pi/4 && v < 1, v][[1]];
ParametricPlot[b /. sol, {t, 0, 1}]
l = NIntegrate[Sqrt[D[x, t]^2 + D[y, t]^2] /. sol, {t, 0, 1}];
Print[NumberForm[100 (l - Pi/2)/(Pi/2), {Infinity, 10}]];
