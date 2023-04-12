
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
prior <- create_prior_grid(mat_rel)
prior
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
#>            [,1]       [,2]       [,3]        [,4]        [,5]
#> [1,] 0.02317701 0.02637331 0.02682577 0.008921896 0.003900771
#> [2,] 0.03500955 0.07297163 0.08035610 0.059660281 0.034823121
#> [3,] 0.05021456 0.09393745 0.08560386 0.083715978 0.055951533
#> [4,] 0.03270899 0.06221307 0.04540975 0.027231408 0.012975970
#> [5,] 0.01510723 0.02301965 0.02464330 0.014067769 0.001180037
#> attr(,"type")
#> [1] "prior"
pod_grid
#>            [,1]      [,2]       [,3]       [,4]       [,5]
#> [1,] 0.15953356 0.5098052 0.31968046 0.20149118 0.52282867
#> [2,] 0.22317107 0.3216747 0.02190087 0.07831000 0.05702751
#> [3,] 0.81412220 0.6174364 0.69174654 0.07994252 0.03070770
#> [4,] 0.01674367 0.9764104 0.67462655 0.96222986 0.58341988
#> [5,] 0.01085092 0.5352397 0.70779074 0.12647581 0.95832521
cost_grid
#>           [,1]        [,2]      [,3]       [,4]       [,5]
#> [1,] 0.3341634 0.298887796 0.7455817 0.40336711 0.63232815
#> [2,] 0.2964412 0.009110933 0.4015101 0.88178914 0.59491710
#> [3,] 0.9308888 0.323172548 0.7324271 0.88388449 0.40244980
#> [4,] 0.4688640 0.576077350 0.7997331 0.01983304 0.02463854
#> [5,] 0.1866726 0.268667586 0.4902931 0.61983910 0.07652470
```

In the global environment should be 3 5 by 5 matrices.

## Searching a sequence of squares

## Optimal search sequence

## Extracting data

## Visualisation
