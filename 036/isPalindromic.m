function isPalin = isPalindromic(str)
% ISPALINDROMIC   Checks if a string STR is palindromic.
%   ISPALINDROMIC(STR) returns true if STR is palindromic and false
%   otherwise.

isPalin = strcmp(str, fliplr(str));
end