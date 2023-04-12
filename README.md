
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
#>             [,1]        [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005291822 0.033717428 0.037821554 0.04277901 0.029362000
#> [2,] 0.019585402 0.072618730 0.066215909 0.04922128 0.021613149
#> [3,] 0.037045080 0.085311218 0.119180614 0.09749977 0.057562229
#> [4,] 0.017004847 0.036563538 0.040342207 0.04408771 0.045158882
#> [5,] 0.002170940 0.003923976 0.008974151 0.02023286 0.006715694
#> attr(,"type")
#> [1] "prior"
pod_grid
#>           [,1]      [,2]      [,3]       [,4]       [,5]
#> [1,] 0.5121576 0.5019632 0.4512139 0.22423766 0.05695826
#> [2,] 0.8870213 0.7943355 0.1944900 0.85620470 0.99638238
#> [3,] 0.3683736 0.5575979 0.9071787 0.04304066 0.54662173
#> [4,] 0.6667221 0.6625831 0.4054581 0.49134987 0.11921877
#> [5,] 0.7629115 0.0554398 0.4942396 0.03821361 0.72414997
cost_grid
#>            [,1]      [,2]      [,3]      [,4]      [,5]
#> [1,] 0.52181204 0.9354728 0.1217525 0.1367235 0.2943632
#> [2,] 0.93386842 0.3264138 0.3773441 0.9621469 0.9622988
#> [3,] 0.05712976 0.4825680 0.9306436 0.5534579 0.5667564
#> [4,] 0.70920742 0.5512074 0.4952179 0.8896544 0.5625641
#> [5,] 0.78037994 0.1899433 0.9606394 0.2507520 0.8547645
```

In the global environment should be 3 5x5 matrices.

To calculate the posterior given a negative search result we use the
`update_posterior_neg()` function. We will assume there as been a
negative search in the grid square in row 5 and column 3.

``` r
posterior_single <- update_posterior_neg(prior_grid, pod_grid, 5 , 3)
posterior_single
#>             [,1]        [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005315397 0.033867644 0.037990055 0.04296959 0.029492812
#> [2,] 0.019672658 0.072942257 0.066510910 0.04944057 0.021709438
#> [3,] 0.037210121 0.085691291 0.119711580 0.09793415 0.057818676
#> [4,] 0.017080606 0.036726434 0.040521937 0.04428413 0.045360071
#> [5,] 0.002180612 0.003941458 0.004558991 0.02032300 0.006745613
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
search_posteriors <- search_sequence_posteriors(prior_grid, pod_grid, search_sequence)
search_posteriors
#> [[1]]
#> [[1]]$posterior
#>             [,1]       [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005300687 0.03377391 0.037884914 0.04285067 0.027735977
#> [2,] 0.019618212 0.07274038 0.066326835 0.04930374 0.021649355
#> [3,] 0.037107138 0.08545413 0.119380267 0.09766310 0.057658657
#> [4,] 0.017033334 0.03662479 0.040409789 0.04416157 0.045234533
#> [5,] 0.002174577 0.00393055 0.008989185 0.02026675 0.006726944
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[1]]$searched_square
#> [1] 1 5
#> 
#> [[1]]$overall_detection
#> [1] 0.4962214
#> 
#> 
#> [[2]]
#> [[2]]$posterior
#>             [,1]        [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005304795 0.033800089 0.037914277 0.04288388 0.027757474
#> [2,] 0.019633417 0.072796760 0.066378242 0.04934195 0.021666135
#> [3,] 0.037135899 0.085520365 0.119472794 0.09773880 0.057703347
#> [4,] 0.017046536 0.036653176 0.040441109 0.04419580 0.045269592
#> [5,] 0.002176262 0.003933596 0.008996152 0.01950739 0.006732158
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[2]]$searched_square
#> [1] 5 4
#> 
#> [[2]]$overall_detection
#> [1] 0.4965764
#> 
#> 
#> [[3]]
#> [[3]]$posterior
#>             [,1]        [,2]        [,3]       [,4]         [,5]
#> [1,] 0.005421840 0.034545856 0.038750820 0.04383008 2.836992e-02
#> [2,] 0.020066610 0.074402953 0.067842817 0.05043064 8.010917e-05
#> [3,] 0.037955268 0.087407292 0.122108850 0.09989531 5.897652e-02
#> [4,] 0.017422652 0.037461895 0.041333404 0.04517094 4.626842e-02
#> [5,] 0.002224279 0.004020387 0.009194644 0.01993781 6.880697e-03
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[3]]$searched_square
#> [1] 2 5
#> 
#> [[3]]$overall_detection
#> [1] 0.4855487
#> 
#> 
#> [[4]]
#> [[4]]$posterior
#>             [,1]       [,2]        [,3]       [,4]         [,5]
#> [1,] 0.005448991 0.03471885 0.038944869 0.04404956 2.851198e-02
#> [2,] 0.020167096 0.07477553 0.068182547 0.05068317 8.051032e-05
#> [3,] 0.038145333 0.08784499 0.122720323 0.10039555 5.927185e-02
#> [4,] 0.017509898 0.03764949 0.041540386 0.04539714 4.650012e-02
#> [5,] 0.002235418 0.00404052 0.009240687 0.02003765 1.907545e-03
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[4]]$searched_square
#> [1] 5 5
#> 
#> [[4]]$overall_detection
#> [1] 0.4843538
#> 
#> 
#> [[5]]
#> [[5]]$posterior
#>             [,1]        [,2]        [,3]       [,4]         [,5]
#> [1,] 0.005631446 0.035881379 0.040248904 0.04552452 2.946668e-02
#> [2,] 0.020842374 0.077279328 0.070465581 0.05238025 8.320614e-05
#> [3,] 0.039422597 0.090786407 0.126829508 0.10375721 2.777237e-02
#> [4,] 0.018096201 0.038910150 0.042931330 0.04691722 4.805713e-02
#> [5,] 0.002310269 0.004175813 0.009550103 0.02070859 1.971418e-03
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[5]]$searched_square
#> [1] 3 5
#> 
#> [[5]]$overall_detection
#> [1] 0.4822689
```

The output of the function will be a list of the length of the search
sequence containing for each step an overall probability of detection,
the searched square and the posterior.

## Optimal search sequence

Given a cost matrix representing the theoretical cost of searching the
each grid square `optimal_search_sequence_posteriors()` will perform the
optimal search of a given length. The output is the same as
`search_sequence_posteriors()`.

``` r
search_posteriors_optim <- optimal_search_sequence_posteriors(prior_grid, pod_grid, cost_grid, 5)
search_posteriors_optim
#> [[1]]
#> [[1]]$posterior
#>             [,1]        [,2]       [,3]       [,4]        [,5]
#> [1,] 0.005365035 0.034183916 0.03834482 0.04337086 0.029768230
#> [2,] 0.019856371 0.073623427 0.06713202 0.04990227 0.021912172
#> [3,] 0.023722376 0.086491518 0.12082951 0.09884870 0.058358615
#> [4,] 0.017240113 0.037069403 0.04090035 0.04469768 0.045783666
#> [5,] 0.002200975 0.003978265 0.00909831 0.02051278 0.006808607
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[1]]$searched_square
#> [1] 3 1
#> 
#> [[1]]$overall_detection
#> [1] 0.4972454
#> 
#> 
#> [[2]]
#> [[2]]$posterior
#>             [,1]        [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005698280 0.036307225 0.040726584 0.04606481 0.031617261
#> [2,] 0.021089734 0.016082243 0.071301877 0.05300191 0.023273230
#> [3,] 0.025195874 0.091863874 0.128334739 0.10498861 0.061983517
#> [4,] 0.018310970 0.039371941 0.043440845 0.04747404 0.048627484
#> [5,] 0.002337687 0.004225372 0.009663445 0.02178692 0.007231519
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[2]]$searched_square
#> [1] 2 2
#> 
#> [[2]]$overall_detection
#> [1] 0.4787919
#> 
#> 
#> [[3]]
#> [[3]]$posterior
#>             [,1]        [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005751664 0.036647367 0.041108129 0.04649637 0.031913466
#> [2,] 0.021287312 0.016232908 0.071969865 0.05349846 0.023491264
#> [3,] 0.016063472 0.092724496 0.129537037 0.10597220 0.062564206
#> [4,] 0.018482515 0.039740795 0.043847819 0.04791880 0.049083048
#> [5,] 0.002359588 0.004264957 0.009753977 0.02199103 0.007299267
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[3]]$searched_square
#> [1] 3 1
#> 
#> [[3]]$overall_detection
#> [1] 0.4798264
#> 
#> 
#> [[4]]
#> [[4]]$posterior
#>             [,1]        [,2]        [,3]       [,4]        [,5]
#> [1,] 0.005860366 0.037339970 0.022985926 0.04737511 0.032516602
#> [2,] 0.021689623 0.016539696 0.073330031 0.05450953 0.023935228
#> [3,] 0.016367057 0.094476906 0.131985171 0.10797498 0.063746614
#> [4,] 0.018831818 0.040491861 0.044676503 0.04882442 0.050010674
#> [5,] 0.002404182 0.004345561 0.009938318 0.02240664 0.007437216
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[4]]$searched_square
#> [1] 1 3
#> 
#> [[4]]$overall_detection
#> [1] 0.4803671
#> 
#> 
#> [[5]]
#> [[5]]$posterior
#>             [,1]        [,2]       [,3]       [,4]       [,5]
#> [1,] 0.006657495 0.042418968 0.02611248 0.05381909 0.03693952
#> [2,] 0.024639855 0.018789432 0.08330441 0.06192394 0.02719091
#> [3,] 0.018593312 0.107327696 0.01391742 0.12266178 0.07241746
#> [4,] 0.021393330 0.045999581 0.05075342 0.05546554 0.05681315
#> [5,] 0.002731200 0.004936647 0.01129013 0.02545440 0.00844883
#> attr(,"type")
#> [1] "posterior"
#> 
#> [[5]]$searched_square
#> [1] 3 3
#> 
#> [[5]]$overall_detection
#> [1] 0.422312
```

## Extracting data

To extract the data from search sequence use the
`posterior_sequence_long()` function. This will create a long format
data-frame from the list output of both search functions.

``` r
#Load tidyverse
library(tidyverse)
#> -- Attaching packages --------------------------------------- tidyverse 1.3.1 --
#> v ggplot2 3.3.5     v purrr   0.3.4
#> v tibble  3.1.6     v dplyr   1.0.9
#> v tidyr   1.1.4     v stringr 1.4.0
#> v readr   2.1.1     v forcats 0.5.1
#> Warning: package 'dplyr' was built under R version 4.1.3
#> -- Conflicts ------------------------------------------ tidyverse_conflicts() --
#> x dplyr::filter() masks stats::filter()
#> x dplyr::lag()    masks stats::lag()

data_long <- posterior_sequence_long(search_posteriors)
data_long_optim <- posterior_sequence_long(search_posteriors_optim)

slice_head(data_long, n = 5)
#>   Var1 Var2           p searched_square overall_detection search_id
#> 1    1    1 0.005300687             1,5         0.4962214         1
#> 2    1    2 0.033773912             1,5         0.4962214         1
#> 3    1    3 0.037884914             1,5         0.4962214         1
#> 4    1    4 0.042850671             1,5         0.4962214         1
#> 5    1    5 0.027735977             1,5         0.4962214         1
slice_head(data_long_optim, n = 5)
#>   Var1 Var2           p searched_square overall_detection search_id
#> 1    1    1 0.005365035             3,1         0.4972454         1
#> 2    1    2 0.034183916             3,1         0.4972454         1
#> 3    1    3 0.038344824             3,1         0.4972454         1
#> 4    1    4 0.043370864             3,1         0.4972454         1
#> 5    1    5 0.029768230             3,1         0.4972454         1
```

## Visualisation
