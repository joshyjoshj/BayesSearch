# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#' Create a prior grid
#'
#' @description 'create_prior_grid' returns a valid prior from a given numeric matrix
#'
#' @details This is a function that takes any numeric matrix and returns another numeric matrix which is a valid probability
#' density function that has a "prior" attribute assigned to it. The input doesn't have to be a valid PDF the function will
#' do this so when using this package its always good to use this function before using any of the search functions.
#'
#' @param prior_input A numeric matrix
#'
#' @returns A (normalized) numeric matrix
#'
#' @examples create_prior_grid(matrix(c(1,2,3,4),nrow = 1, ncol = 4))
#'
#'
#' @export
create_prior_grid <- function(prior_input) {
    .Call(`_BayesSearch_create_prior_grid`, prior_input)
}

#' Optimal search posteriors
#'
#' @description Calculates the posteriors of the optimal search of a given length
#'
#' @details This function takes a cost grid in addition to the standard prior grid and probability of detection grid and will calculate the optimal
#' search sequence for a given length.
#'
#' @param prior_grid A numeric matrix that is a valid probability density function. Use \code{\link{create_prior_grid}} for validation.
#'
#' @param pod_grid A numeric matrix. All matrix entries must be greater than 0 and less than 1.
#'
#' @param cost_grid A numeric matrix representing the cost of searching each grid square
#'
#' @param num_searches Integer representing the number of searches to perform
#'
#' @returns List of the same length as the search sequence. Each list element contains a posterior (Numeric Matrix), overall probability
#' of detection (Double) and the grid square searched (String)
#'
#' @examples
#'
#' generate_sample_matrix(5)
#' optimal_search_sequence_posteriors(prior_grid, pod_grid, cost_grid, 10)
#'
#' @export
optimal_search_sequence_posteriors <- function(prior_grid, pod_grid, cost_grid, num_searches) {
    .Call(`_BayesSearch_optimal_search_sequence_posteriors`, prior_grid, pod_grid, cost_grid, num_searches)
}

#' Melt Search sequence output
#'
#' @description Melt the output of search sequence functions into long data-frame format
#'
#' @details This function melts the output of a search function to a long data-frame format to allow for easier analysis
#' of the searcg
#'
#' @param search_posteriors, the list output of a search function
#'
#' @returns A dataframe
#'
#' @examples
#' generate_sample_matrix(5)
#' search_sequence <- matrix(c(1,5,2,5,3,5,4,5,5,5), nrow = 5, ncol = 2)
#' search_posteriors <- search_sequence_posteriors(prior_grid, pod_grid, search_sequence)
#' posterior_sequence_long(search_posteriors)
#'
#' @export
posterior_sequence_long <- function(search_posteriors) {
    .Call(`_BayesSearch_posterior_sequence_long`, search_posteriors)
}

#' Posteriors of a search list
#'
#' @description Calculates the posteriors for each step in a given search sequence.
#'
#' @details This function will calculate the posteriors and overall probability of detection for each step in a given search sequence matrix.
#' The function assumes a negative search result after each step.
#'
#' @param prior_grid A numeric matrix that is a valid probability density function. Use \code{\link{create_prior_grid}} for validation.
#'
#' @param pod_grid A numeric matrix. All matrix entries must be greater than 0 and less than 1.
#'
#' @param search_sequence An integer matrix with two columns. Each row represents the square to be searched. Column 1 is the row index
#' and column 2 is the column index. See example for more detail.
#'
#' @returns List of the same length as the search sequence. Each list element contains a posterior (Numeric Matrix), overall probability
#' of detection (Double) and the grid square searched (String)
#'
#' @examples
#' generate_sample_matrix(5)
#' search_sequence <- matrix(c(1,5,2,5,3,5,4,5,5,5), nrow = 5, ncol = 2)
#' search_sequence_posteriors(prior_grid, pod_grid, search_sequence)
#'
#' @export
search_sequence_posteriors <- function(prior_grid, pod_grid, search_sequence) {
    .Call(`_BayesSearch_search_sequence_posteriors`, prior_grid, pod_grid, search_sequence)
}

#' Calculate the posterior distribution
#'
#' @description Calculate the posterior distribution after a negative search of a given grid square
#'
#' @details This function will calculate the posterior distribution from a given prior matrix, probability of detection matrix
#' and a column and row index.
#'
#' @param prior_grid A numeric matrix that is a valid probability density function. Use \code{\link{create_prior_grid}} for validation.
#'
#' @param pod_grid A numeric matrix. All matrix entries must be greater than 0 and less than 1.
#'
#' @param row Integer representing the row index
#'
#' @param col Integer representing the column index
#'
#' @returns Numeric matrix
#'
#' @examples
#' generate_sample_matrix(5)
#' update_posterior_neg(prior_grid, pod_grid, 1, 1)
#'
#' @export
update_posterior_neg <- function(prior_grid, pod_grid, row, col) {
    .Call(`_BayesSearch_update_posterior_neg`, prior_grid, pod_grid, row, col)
}

