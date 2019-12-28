SetOptions[$Output, FormatType->OutputForm];
volume[a_, b_, t_] := 
  2 Pi NIntegrate[(t/Sqrt[(a/b Tan[\[Theta]])^2 + 1] + 
        a Cos[\[Theta]])^2 D[
       t/Sqrt[(b/a Cot[\[Theta]])^2 + 1] + 
        b Sin[\[Theta]], \[Theta]], {\[Theta], 0, Pi/2}] - 
   4/3 Pi a^2 b;
Print[NumberForm[volume[3, 1, 1], {Infinity, 8}]];
