
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
`generate_sample_matrix()`. This will assign 3 matrices to the global
environment for use in examples

``` r
generate_sample_matrix(5)
prior_grid
#>             [,1]       [,2]       [,3]        [,4]         [,5]
#> [1,] 0.004672396 0.02259187 0.03615225 0.007195053 0.0001865325
#> [2,] 0.051125526 0.07731457 0.09669828 0.039834787 0.0105480508
#> [3,] 0.086162423 0.10642794 0.10176379 0.092756460 0.0439304498
#> [4,] 0.012274005 0.03070826 0.06178463 0.042532490 0.0063445901
#> [5,] 0.002480093 0.02936686 0.02737386 0.008749487 0.0010253495
#> attr(,"type")
#> [1] "prior"
pod_grid
#>             [,1]      [,2]      [,3]      [,4]       [,5]
#> [1,] 0.378385781 0.9886960 0.2062423 0.1113824 0.07083451
#> [2,] 0.400885585 0.9746022 0.5596461 0.5526625 0.34121110
#> [3,] 0.006066308 0.5473308 0.4904086 0.8477959 0.94537991
#> [4,] 0.173472489 0.1761818 0.4884321 0.5347991 0.47121327
#> [5,] 0.206943102 0.5142227 0.8819806 0.5437130 0.94504692
cost_grid
#>           [,1]      [,2]      [,3]       [,4]      [,5]
#> [1,] 0.9989569 0.8935681 0.5158500 0.80008722 0.8565015
#> [2,] 0.6693635 0.8615648 0.7943506 0.45035811 0.1683589
#> [3,] 0.1438332 0.4151704 0.9054246 0.65861904 0.1292251
#> [4,] 0.7165316 0.6159287 0.4912922 0.26161934 0.1111751
#> [5,] 0.7477122 0.9245115 0.1093750 0.08136329 0.7568129
```

In the global environment should be 3 5x5 matrices.

To calculate the posterior given a negative search result we use the
`update_posterior_neg()` function. We will assume there as been a
negative search in the grid square in row 5 and column 3.

``` r
posterior_single <- update_posterior_neg(prior_grid, pod_grid, 5 , 3)
posterior_single
#>             [,1]       [,2]        [,3]        [,4]         [,5]
#> [1,] 0.004787993 0.02315080 0.037046677 0.007373062 0.0001911474
#> [2,] 0.052390398 0.07922737 0.099090647 0.040820320 0.0108090152
#> [3,] 0.088294127 0.10906103 0.104281478 0.095051304 0.0450173124
#> [4,] 0.012577670 0.03146800 0.063313215 0.043584766 0.0065015586
#> [5,] 0.002541452 0.03009341 0.003310574 0.008965954 0.0010507172
#> attr(,"type")
#> [1] "posterior"
```

The posterior is outputted as a matrix with attribute “posterior”.

## Searching a sequence of squares

Now say we want to simulate a sequence of failed searches. To do this we
first define a matrix of squares to search.

``` r
#Defining search sequence
search_sequence <- matrix(c(1,5,2,5,3,5,4,5,5,5), nrow = 5, ncol = 2)
search_sequence
#>      [,1] [,2]
#> [1,]    1    5
#> [2,]    5    4
#> [3,]    2    5
#> [4,]    5    5
#> [5,]    3    5
```

This search sequence indicates 5 searches starting at (1,5) then (5,4)
and so on, ending at (3,5). The first column is the row index and second
the column. Now this matrix can be passed into the
`search_sequence_posteriors()` function.

``` r
#
search_posteriors <- search_sequence_posteriors(prior_grid, pod_grid, search_sequence)
search_posteriors
#> [[1]]
#> [[1]]$posterior
#>             [,1]       [,2]       [,3]        [,4]         [,5]
#> [1,] 0.004672458 0.02259216 0.03615273 0.007195148 0.0001733218
#> [2,] 0.051126201 0.07731559 0.09669956 0.039835313 0.0105481902
#> [3,] 0.086163562 0.10642935 0.10176513 0.092757685 0.0439310303
#> [4,] 0.012274167 0.03070867 0.06178545 0.042533052 0.0063446740
#> [5,] 0.002480126 0.02936725 0.02737422 0.008749603 0.0010253631
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[1]]$searched_square
#> [1] 1 5
#> 
#> [[1]]$overall_detection
#> [1] 0.5457451
#> 
#> 
#> [[2]]
#> [[2]]$posterior
#>             [,1]       [,2]       [,3]        [,4]         [,5]
#> [1,] 0.004694792 0.02270016 0.03632554 0.007229541 0.0001741503
#> [2,] 0.051370585 0.07768516 0.09716178 0.040025726 0.0105986107
#> [3,] 0.086575425 0.10693808 0.10225157 0.093201068 0.0441410212
#> [4,] 0.012332838 0.03085545 0.06208078 0.042736360 0.0063750016
#> [5,] 0.002491981 0.02950763 0.02750507 0.004011413 0.0010302643
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[2]]$searched_square
#> [1] 5 4
#> 
#> [[2]]$overall_detection
#> [1] 0.5457549
#> 
#> 
#> [[3]]
#> [[3]]$posterior
#>             [,1]       [,2]       [,3]        [,4]         [,5]
#> [1,] 0.004711832 0.02278255 0.03645738 0.007255780 0.0001747824
#> [2,] 0.051557034 0.07796712 0.09751443 0.040170999 0.0070075891
#> [3,] 0.086889649 0.10732621 0.10262269 0.093539341 0.0443012305
#> [4,] 0.012377599 0.03096744 0.06230610 0.042891471 0.0063981396
#> [5,] 0.002501026 0.02961472 0.02760490 0.004025973 0.0010340037
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[3]]$searched_square
#> [1] 2 5
#> 
#> [[3]]$overall_detection
#> [1] 0.5464972
#> 
#> 
#> [[4]]
#> [[4]]$posterior
#>             [,1]       [,2]       [,3]        [,4]         [,5]
#> [1,] 0.004716440 0.02280483 0.03649304 0.007262877 1.749533e-04
#> [2,] 0.051607464 0.07804338 0.09760981 0.040210292 7.014443e-03
#> [3,] 0.086974639 0.10743119 0.10272307 0.093630835 4.434456e-02
#> [4,] 0.012389706 0.03099773 0.06236705 0.042933425 6.404398e-03
#> [5,] 0.002503472 0.02964369 0.02763190 0.004029911 5.687727e-05
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[4]]$searched_square
#> [1] 5 5
#> 
#> [[4]]$overall_detection
#> [1] 0.5461074
#> 
#> 
#> [[5]]
#> [[5]]$posterior
#>             [,1]       [,2]       [,3]        [,4]         [,5]
#> [1,] 0.004922817 0.02380270 0.03808986 0.007580678 1.826087e-04
#> [2,] 0.053865644 0.08145831 0.10188091 0.041969768 7.321373e-03
#> [3,] 0.090780376 0.11213204 0.10721791 0.097727826 2.528088e-03
#> [4,] 0.012931841 0.03235410 0.06509603 0.044812057 6.684634e-03
#> [5,] 0.002613016 0.03094081 0.02884099 0.004206247 5.936604e-05
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[5]]$searched_square
#> [1] 3 5
#> 
#> [[5]]$overall_detection
#> [1] 0.5286365
```

The output of the function will be a list of the length of the search
sequence containing for each step an overall probability of detection,
the searched square and the posterior.

## Optimal search sequence

## Extracting data

## Visualisation
