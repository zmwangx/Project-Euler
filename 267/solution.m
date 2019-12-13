SetOptions[$Output, FormatType->OutputForm];
Print[NumberForm[N[Sum[Binomial[1000, k], {k, 432, 1000}]/2^1000], 12]];
