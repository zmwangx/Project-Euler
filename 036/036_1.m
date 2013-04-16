%
% prbl036_1.m
% Prbl036
% Project Euler
%
% Created by Zhiming Wang on 12/07/2012.
% --------------------------------------
% Algorithm:
%
% This is the brute force version.
% --------------------------------
% Answer: 872187
%

% Constants
RANGE = 1000000;

% Search
dualPalins = [];
for n = 1:RANGE
    if isPalindromic(int2str(n))
        if isPalindromic(dec2bin(n))
            dualPalins(end + 1) = n;
        end
    end
end
disp(dualPalins);
disp('sum: '); disp(sum(dualPalins));