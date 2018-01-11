# mgsubcpp
C++11 version of mgsub

## Comparing mgsub to mgsubcpp to qdap

These are microbenchmarks from my laptop comparing performance between the three packages named above.  As of this 1/11/2018, the C++ code is fairly terrible when regular expressions are involved in matching/replacing.  Need to determine why.

```r
library(mgsub)
library(mgsubcpp)
library(qdap)
library(microbenchmark)
```

## First test

Shift the words in "hey, how are you?" one to the left. The solution is incorrect for qdap.


```r
s = "hey, how are you?"
m = c("hey","how","are","you")
r = c("how","are","you","hey")
names(r) = m

microbenchmark(
  mgsub = mgsub::mgsub(s,r),
  mgsubcpp = mgsubcpp::mgsub(s,r),
  qdap = qdap::mgsub(m,r,s,fixed=FALSE)
)
```

```
## Unit: microseconds
##      expr     min       lq     mean   median       uq       max neval
##     mgsub 320.547 375.0655 654.5899 396.2165 456.2050 21367.935   100
##  mgsubcpp  71.841  82.4160 105.5841  87.5220 109.4025   334.770   100
##      qdap 166.290 176.6840 311.4885 195.6470 237.2195  9332.677   100
```

## Second test

Including regular expressions in the match and replacement.


```r
s = "Dopazamine is not the same as Dopachloride and is still fake."
m = c("[Dd]opa(.*?mine)","fake")
r = c("Meta\\1","real")
names(r) = m

microbenchmark(
  mgsub = mgsub::mgsub(s,r),
  mgsubcpp = mgsubcpp::mgsub(s,r),
  qdap = qdap::mgsub(m,r,s,fixed=FALSE)
)
```

```
## Unit: microseconds
##      expr      min        lq      mean    median       uq      max neval
##     mgsub  178.689  196.5585  252.3352  223.3620  276.969  781.127   100
##  mgsubcpp 2040.339 2168.7030 2401.3670 2280.6565 2469.921 4240.037   100
##      qdap  159.727  169.7555  217.3851  186.1655  240.684  502.154   100
```

## Third test

Both of the previous examples are small. This time we'll use the first chapter of Moby Dick.  Matches and replacements use regular expressions. Matches are based on the most commonly occuring words (to make lots of work).




```r
s = "Call me Ishmael..." #full text not displayed here
```


```r
# Test 3 -----------
m = c("the","(\\b)of(\\b)","and","(\\b)a(\\b)","they","(\\b)to(\\b)","(\\b)in(\\b)","(\\b)i(\\b)")
r = c("a","\\1in\\2","not","\\1the\\2","we","\\1from\\2","\\1out\\2","\\1you\\2")
names(r) = m

microbenchmark(
  mgsub = mgsub::mgsub(s,r),
  mgsubcpp = mgsubcpp::mgsub(s,r),
  qdap = qdap::mgsub(m,r,s,fixed=FALSE)
)
```

```
## Unit: milliseconds
##      expr         min          lq        mean      median          uq
##     mgsub  219.164735  224.571539  265.626687  279.515155  288.435388
##  mgsubcpp 1516.387796 1532.941336 1608.825134 1544.935205 1581.385227
##      qdap    2.710605    2.887471    4.484652    3.008906    3.325259
##         max neval
##   368.31033   100
##  2779.68035   100
##    67.78079   100
```
