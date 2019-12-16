SetOptions[$Output, FormatType->OutputForm];
p[k_, n_] :=
  1 - Sum[Multinomial[l, k - 2 l, n - k + l] k!/2^l, {l, 0, k/2}]/n^k;
Print[NumberForm[N[p[20000, 1000000]], 10]];
