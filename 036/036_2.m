%
% prbl036_2.m
% Prbl036
% Project Euler
%
% Created by Zhiming Wang on 12/07/2012.
% --------------------------------------
% Algorithm:
%
% This version use the first half of decimal palindromes as generators,
% thus greatly reduces the number of vain searches.
% -------------------------------------------------
% Answer: 872187
%

% Constants
MAX_NUMBER_OF_DIGITS = 6;

%Search
dualPalins = [];
for generatorNDigits = 1:ceil(MAX_NUMBER_OF_DIGITS / 2)
    for generator = 10^(generatorNDigits-1):(10^generatorNDigits - 1)
        
        firstHalf = int2str(generator);
        firstHalfReverse = fliplr(firstHalf);

        % Deal with palindromes with the form {a1, a2, ... , an-1, an, 
        % an-1, ... , a2, a1}.
        secondHalf = firstHalfReverse(2:end);
        decimalString = strcat(firstHalf, secondHalf);
        decimal = str2num(decimalString);
        if isPalindromic(dec2bin(decimal))
            dualPalins(end+1) = decimal;
        end
        
        % Deal with palindromes with the form {a1, a2, ... , an-1, an, an,
        % an-1, ... , a2, a1}, if needed.
        if generatorNDigits * 2 <= MAX_NUMBER_OF_DIGITS
            secondHalf = firstHalfReverse;
            decimalString = strcat(firstHalf, secondHalf);
            decimal = str2num(decimalString);
            if isPalindromic(dec2bin(decimal))
                dualPalins(end+1) = decimal;
            end
        end
    end
end
disp(dualPalins);
disp('sum: '); disp(sum(dualPalins));