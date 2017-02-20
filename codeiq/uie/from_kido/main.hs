module Main where

import Data.Ratio


fact :: (Integral a) => a -> a -> Ratio a
fact n m = if m <= 1 then 1 % n else (m % n) * fact n (m-1)

pow :: (Integral a) => Ratio a -> a -> Ratio a
pow base exp
    | exp == 0  = 1
    | exp == 1  = base
    | otherwise = base * pow base (exp-1)

factor :: (Integral a) => a -> a -> a -> [Ratio a]
factor n m k
    | m == 1 = [pow (1 % n) k]
    | otherwise = concat $ map (\i -> f n m k i) [0..k]
        where
            f n m k i = map (\x -> base n m i * x) $ factor n (m-1) (k-i)
            base n m i = pow (m % n) i

print_format :: (Integral a) => [Ratio a] -> IO Bool
print_format xs = do
        let x = sum xs
        print $ concat [x " " (fromRational x)]
        return $ x > 1 % 2

main :: IO ()
main = do
    -- print $ factor 365 365 3
    filter print_format $ map 

