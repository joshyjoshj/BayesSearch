
<!-- README.md is generated from README.Rmd. Please edit that file -->

# BayesSearch

<!-- badges: start -->
<!-- badges: end -->

The package gives functions to implement Bayesian Search theory in R
from start to finish. There are helper functions to create valid
probability density functions and 3 different search types as well as a
custom melt function to aid visualization and analysis.

## Installation

You can install the development version of BayesSearch from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("joshyjoshj/BayesSearch")
```

## Creating a valid prior

The first step in any Bayesian modelling is thinking about your problem
and setting a prior. In the case of search theory this would be the
likely distribution of the location of the object. Maybe the easiest way
to think about this on a small scale is to think about the values of the
grid squares relative to each other. For example consider a 2 by 2
matrix. Picking row 1 and column 2 (1,2) as an initial grid square we
can assign a value of 1 to it. Now square (2,1) we think is twice as
likely as (1,2) to contain the object as (1,1) hence we assign a value
of 2 to this square. This can be repeated for the other 2 values and
lets say gives the matrix:

$$ \begin{pmatrix} 3 & 1 \\ 2 & 5 \end{pmatrix} $$

However, this is not a valid distribution as the sum of the entries is
not 1. We can use the `create_prior_grid()` function to solve this:

``` r
#Loading package
library(BayesSearch)

#Creating relative value matrix
mat_rel <- matrix(c(3,2,1,5), nrow = 2, ncol = 2)

#Creating prior using create_prior_grid function
prior_grid <- create_prior_grid(mat_rel)
prior_grid
#>           [,1]       [,2]
#> [1,] 0.2727273 0.09090909
#> [2,] 0.1818182 0.45454545
#> attr(,"type")
#> [1] "prior"
```

You don’t need to use this function before using any of the search
functions but if the matrix entered as the prior is not valid you well
get errors.

## Searching a grid sqaure

For the rest of the examples we will use example matrices created by
`generate_sample_matrix()`. This will assing 3 matrices to the global
environment for use in examples

``` r
generate_sample_matrix(5)
prior_grid
#>           [,1]       [,2]
#> [1,] 0.2727273 0.09090909
#> [2,] 0.1818182 0.45454545
#> attr(,"type")
#> [1] "prior"
pod_grid
#>            [,1]      [,2]      [,3]       [,4]      [,5]
#> [1,] 0.95867317 0.1205169 0.7296552 0.80273744 0.3288860
#> [2,] 0.89862219 0.6426181 0.9946260 0.05737373 0.3100916
#> [3,] 0.94947968 0.9148073 0.1947410 0.13404848 0.2086192
#> [4,] 0.01561018 0.5322052 0.3546162 0.70401892 0.1381261
#> [5,] 0.29490816 0.1925097 0.5197416 0.70729174 0.5304901
cost_grid
#>           [,1]        [,2]      [,3]      [,4]        [,5]
#> [1,] 0.5802871 0.223475603 0.7309814 0.4312094 0.855597302
#> [2,] 0.3118946 0.261471343 0.8926397 0.9157667 0.898218545
#> [3,] 0.1447746 0.185107801 0.5933187 0.7332843 0.744961950
#> [4,] 0.3907267 0.304641210 0.9543420 0.4153328 0.005037962
#> [5,] 0.4347330 0.007389252 0.4006728 0.4923801 0.818887146
```

In the global environment should be 3 5 by 5 matrices.

## Searching a sequence of squares

## Optimal search sequence

## Extracting data

## Visualisation
