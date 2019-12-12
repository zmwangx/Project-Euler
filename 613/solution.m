SetOptions[$Output, FormatType->OutputForm];
Print[NumberForm[
  NIntegrate[(Pi/2 + ArcCot[(3 - y)/x] + ArcCot[(4 - x)/y])/(12 Pi)
     Boole[3 x + 4 y <= 12], {x, 0, 4}, {y, 0, 3}, AccuracyGoal -> 10,
    PrecisionGoal -> 10], 10]]
