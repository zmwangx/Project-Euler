SetOptions[$Output, FormatType->OutputForm];
t[n_, k_] := t[n, k] = Which[
    n >= 1 && k == 1, 1,
    k >= 2 && k <= n - 1, Binomial[n - 1, k - 1] t[k, k],
    n >= 2 && k == n, n! - Sum[t[n, i], {i, 1, n - 1}]];
s[n_] := s[n] =
   If[n == 1,
    0, (Sum[t[n, k] s[k], {k, 1, n - 1}] + n! - 1)/(n! - t[n, n])];
Print[NumberForm[N[s[52]], {Infinity, 8}]];
