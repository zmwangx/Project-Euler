a = N[Log[10, 2], 30];
min = N[Log[10, 1.23], 30];
max = N[Log[10, 1.24], 30];
elligibleQ = min < FractionalPart[a #] < max &;
j = 90; count = 1; targetCount = 678910;
While[True, 
  j = Which[elligibleQ[j + 196], j + 196, elligibleQ[j + 289], 
    j + 289, elligibleQ[j + 485], j + 485, True, 
    Throw["cannot advance", j]]; count++; 
  If[count == targetCount, Print[j]; Break[], Null]];
