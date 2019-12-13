repeat[elem_, n_] := Sequence @@ ConstantArray[elem, n];
partialQuotientSum[divisors_, length_, lengthExact_: False,
   print_: False] :=
  Block[{pool, smallestMultiple, sum = 0, outliers = {}},
   pool = FromDigits /@
     If[lengthExact, Tuples[{{1, 2}, repeat[{0, 1, 2}, length - 1]}],
      Drop[Tuples[{0, 1, 2}, length], 1]];
   Scan[With[{n = #},
      smallestMultiple = SelectFirst[pool, #~Mod~n == 0 &, 0];
      If[print && smallestMultiple > 0,
       Print[n, ":", smallestMultiple], Null];
      If[smallestMultiple > 0, sum += smallestMultiple/n,
       AppendTo[outliers, n]]] &, divisors];
   {sum, outliers}];

quotientSum[divisors_, startingLength_] :=
  Block[{outliers = divisors, length = startingLength, sum = 0,
    partialSum},
   While[Length[outliers] > 0,
    Print["Trying ", length, " digits... (", Length[outliers],
     " left)"];
    {partialSum, outliers} =
     partialQuotientSum[outliers, length, length != startingLength];
    sum += partialSum;
    length++];
   sum];

sum = 11112222222222222222/9999;
sum += quotientSum[Range[9998]~Join~{10000}, 9];
Print[sum];
