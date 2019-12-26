FibonacciMod[n_, m_] := 
 Flatten[Algebra`MatrixPowerMod[{{0, 1}, {1, 1}}, n, m]][[{1, 2, 
    4}]];
n = 10^18; p = 1000000009;
{fnm1, fn, fnp1} = FibonacciMod[n, p];
pow2n = PowerMod[2, n, p];
a = (pow2n - fnp1) fnm1 + fn^2;
b = (pow2n - fnp1) (pow2n - fnm1) - fn^2;
Print[Mod[a ModularInverse[b, p], p]];
