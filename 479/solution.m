n = 1000000; p = 1000000007;
Print[Sum[(1 - ModularInverse[k, p]^2) (PowerMod[1 - k^2, n, p] - 1), {k, 1, n}]~Mod~p];
