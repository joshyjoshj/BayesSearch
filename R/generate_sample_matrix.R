#' Generate sample matrices
#'
#' @param n An integer representing the number of rows and columns for the square matrices
#'
#' @return A Prior, Probability of Detection (POD) and a cost matrix stored in the global environment
#'
#' @import MASS
#' @export
#'
generate_sample_matrix <- function(n){
  x_prior <- rnorm(n^2)
  y_prior <- rnorm(n^2)
  prior_kde <- MASS::kde2d(x_prior,y_prior,n=n)
  prior_matrix <- create_prior_grid(prior_kde$z)
  assign("prior_grid",prior_matrix, envir = .GlobalEnv)

  pod_matrix <- matrix(runif(n^2, min = 0, max = 1), nrow = n, ncol = n)
  assign("pod_grid",pod_matrix, envir = .GlobalEnv)

  cost_matrix <- matrix(runif(n^2, min = 0, max = 1), nrow = n, ncol = n)
  assign("cost_grid",cost_matrix, envir = .GlobalEnv)

}


