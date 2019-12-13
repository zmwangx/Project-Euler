SetOptions[$Output, FormatType->OutputForm];
Print[NumberForm[
  Integrate[
    Pi (v^2 (v^2 - 2 g y))/g^2, {y, -h, v^2/(2 g)}] /. {h -> 100, 
    v -> 20, g -> 9.81}, {20, 4}, 
  ScientificNotationThreshold -> {-Infinity, Infinity}]];
