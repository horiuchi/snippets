module Main where

import Control.Monad (forM_)
import Control.Monad.ST (ST,runST)
import Data.Array.IArray (assocs)
import Data.Array.MArray (freeze,newArray,readArray,writeArray)
import Data.Array.ST (STUArray)
import Data.Array.Unboxed (UArray)
import qualified Data.ByteString.Lazy.Char8 as C
import Data.Char (ord)
import Data.Digest.Pure.SHA (sha1,bytestringDigest)
import Data.List (sort)
import GHC.Int (Int64)

type PigData = UArray Int Int
type STPigData s = STUArray s Int Int

getdata :: GHC.Int.Int64 -> Int
getdata n = packR $ bytestringDigest $ sha1 $ C.pack $ show q
    where
        (q, r) = divMod n 10
        packR bs = ((ord $ C.index bs (r * 2)) * 0x100) + (ord $ C.index bs (r * 2 + 1))


getsign :: GHC.Int.Int64 -> Int -> Int
getsign count skips = sum $ skip ls skips
    where
        ls = sort $ map getdata [0..count-1]
        skip :: [Int] -> Int -> [Int]
        skip (x:xs) n = x : skip (drop (n-1) xs) n
        skip []     _ = []


createPigData :: GHC.Int.Int64 -> PigData
createPigData count = runST $ do
    field <- newArray (0, 65535) 0 :: ST s (STPigData s)
    forM_ [0..(count `div` 10)-1] $ \n -> do
        let bs = bytestringDigest $ sha1 $ C.pack $ show n
        forM_ [0..9] $ \r -> do
            let i = packR bs r
            val <- readArray field i
            writeArray field i (val + 1)
    freeze field
        where
            packR bs r = ((ord $ C.index bs (r * 2)) * 0x100) + (ord $ C.index bs (r * 2 + 1))

collect :: Int -> Int -> [(Int, Int)] -> [Int]
collect _ _ [] = []
collect n s l@((x,c):xs)
    | c == 0 = collect n s xs
    | c <= s = collect n (s - c) xs
    | s < c  = x : collect n (n + (s - c + 1)) l

getsign' :: GHC.Int.Int64 -> Int -> Int
getsign' count skips = sum $ collect skips 0 $ assocs $ createPigData count


main :: IO()
main = do
        let count = 107374182400
        let skips = 16777216
        let pig = assocs $ createPigData count
        print pig
        print "Create PigData complete."
        print $ sum $ collect skips 0 pig

