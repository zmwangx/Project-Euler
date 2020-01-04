mod = 17^7;
order = MultiplicativeOrder[2, mod];
inv15 = ModularInverse[15, mod];
k = 10^18;
power = PowerMod[10, k, order];
Print[Mod[(inv15 (6 #^2 - 20 # - 1) + 1) &@PowerMod[2, power, mod], 
   mod]];
