function nPrimeDivisors = computePrimeDivisorNumber(n)
% COMPUTEPRIMEDIVISORNUMBER Computes the number of prime divisors of the 
% positive integer n.

nPrimeDivisors = length(unique(factor(n)));
end