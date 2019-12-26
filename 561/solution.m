u[n_] := Sum[Floor[n/2^i], {i, 1, Infinity}];
q[n_] := u[Floor[n/2]] + 904961 u[Ceiling[n/2]];
Print[q[10^12]];
