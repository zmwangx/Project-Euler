%
% prbl047.m
% Prbl047
% Project Euler
%
% Created by Zhiming Wang on 12/07/12.
% ------------------------------------
% Algorithm:
% 
% Brute force search.
% -------------------
% Answer:
%

n = 1;
while (true)
    if      (computePrimeDivisorNumber(n)     == 4) & ...
            (computePrimeDivisorNumber(n + 1) == 4) & ...
            (computePrimeDivisorNumber(n + 2) == 4) & ...
            (computePrimeDivisorNumber(n + 3) == 4)
        disp(n);
        disp(factor(n));
        disp(n + 1);
        disp(factor(n + 1));
        disp(n + 2);
        disp(factor(n + 2));
        disp(n + 3);
        disp(factor(n + 3));
        break;
    end
    n = n + 1;
end