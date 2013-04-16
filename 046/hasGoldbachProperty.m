function canBeDivided = hasGoldbachProperty(n)
% HASGOLDBACHPROPERTY Checks if the odd composite number n can be written 
% in the form p+2k^2, where p is a prime number and k^2 is a perfect
% square.
if ((mod(n, 2) == 0) | isprime(n))
    disp('Invalid input. Input should be an odd composite number.');
    canBeDivided = false;
    return
end
maxK = floor(sqrt(n/2));
for k = 1:maxK
    if isprime(n - 2 * k.^2)
        canBeDivided = true;
        return
    end
end
canBeDivided = false;
end