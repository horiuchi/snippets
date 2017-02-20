import Data.Char
 
{-
  -- 筆算による開平法 --
-}
squareRoot :: String -> String
squareRoot cs = root' (int' ++ frac' ++ repeat '0') 0 0
  where
    (int, frac) = break (== '.') cs
    int'  = if odd (length int) then ('0' : int) else int
    frac' = if null frac then "." else frac
    root' ('.' : xs) r d   = '.' : root' xs r d
    root' (a : b : xs) r d = (intToDigit . fromIntegral) n' : root' xs r' d'
      where
        n  = r * 100 + read [a, b]
        n' = last $ takeWhile (\x -> (d + x) * x <= n) [0 .. 9]
        r' = n - (d + n') * n'
        d' = 10 * (d + n' + n')

main = do
    print $ take 20 $ drop (2016 + 2) $ squareRoot "2016"
