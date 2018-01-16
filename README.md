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

Shift the words in "hey, how are you?" one to the left. The solution is incorrect for qdap. *January 16, 2018 commit modifying regex creation to happen only once and via a lambda function as resulted in a 30% decrease in compute time*


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
##      expr     min       lq      mean  median      uq       max neval
##     mgsub 323.830 379.8065 654.88963 395.852 439.431 20094.159   100
##  mgsubcpp  46.314  54.5190  73.03722  60.354  66.736   670.997   100
##      qdap 165.926 175.0430 298.99524 179.784 188.354 10327.513   100
```


## Second test

Including regular expressions in the match and replacement. *January 16, 2018 commit modifying regex creation to happen only once and via a lambda function as resulted in a **65%** decrease in compute time*


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
##      expr     min       lq     mean   median        uq      max neval
##     mgsub 185.983 231.0205 368.6695 291.7385  439.9775 2259.143   100
##  mgsubcpp 557.949 640.7295 820.3705 762.5295 1006.6780 1422.951   100
##      qdap 165.561 196.3770 297.5950 228.6495  310.8840 2884.192   100
```

## Third test

Both of the previous examples are small. This time we'll use the first chapter of Moby Dick.  Matches and replacements use regular expressions. Matches are based on the most commonly occuring words (to make lots of work). *January 16, 2018 commit modifying regex creation to happen only once and via a lambda function as resulted in **no change** in compute time*

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
##      expr         min          lq        mean      median          uq          max neval
##     mgsub  216.257080  224.222793  271.478669  280.656885  290.088214   419.172633   100
##  mgsubcpp 1498.768503 1544.225966 1675.795059 1584.527513 1700.526223  2557.007720   100
##      qdap    2.688728    2.811075    3.359294    3.077285    3.425183     9.958464   100
```