%
% prbl046.m
% Prbl046
% Project Euler
%
% Created by Zhiming Wang on 12/07/12.
% ------------------------------------
% Algorithm:
%
% Brute force search.
% -------------------
% Answer: 5777
%

oddComposite = 1;
while true
    oddComposite = oddComposite + 2;
    if isprime(oddComposite)
        continue
    end
    
    if ~hasGoldbachProperty(oddComposite)
        disp(oddComposite);
        break;
    end
end
