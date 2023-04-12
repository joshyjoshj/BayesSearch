#include <Rcpp.h>
using namespace Rcpp;


// Check if the sum of all elements of prior_grid is eqaul to 1
bool check_prior_grid_validity(NumericMatrix prior_grid) {
  double sum = 0;
  for (int r = 0; r < prior_grid.nrow(); ++r) {
    for (int c = 0; c < prior_grid.ncol(); ++c) {
      sum += prior_grid(r, c);
    }
  }
  return (abs(sum - 1) < 1e-6); // Allow for a small numerical error
}

// Check if all elements of the pod_grid matrix are greater than 0 and less than 1
bool check_pod_grid_validity(NumericMatrix pod_grid) {
  for (int r = 0; r < pod_grid.nrow(); ++r) {
    for (int c = 0; c < pod_grid.ncol(); ++c) {
      if (pod_grid(r, c) <= 0 || pod_grid(r, c) >= 1) {
        return false;
      }
    }
  }
  return true;
}

//' Calculate the posterior distribution
//'
//' @description Calculate the posterior distribution after a negative search of a given grid square
//'
//' @details This function will calculate the posterior distribution from a given prior matrix, probability of detection matrix
//' and a column and row index.
//'
//' @param prior_grid A numeric matrix that is a valid probability density function. Use \code{\link{create_prior_grid}} for validation.
//'
//' @param pod_grid A numeric matrix. All matrix entries must be greater than 0 and less than 1.
//'
//' @param row Integer representing the row index
//'
//' @param col Integer representing the column index
//'
//' @returns Numeric matrix
//'
//' @examples
//' generate_sample_matrix(5)
//' update_posterior_neg(prior_grid, pod_grid, 1, 1)
//'
//' @export
// [[Rcpp::export]]
NumericMatrix update_posterior_neg(NumericMatrix prior_grid, NumericMatrix pod_grid, int row, int col) {
  row -= 1; // Subtract 1 to convert to 0-based indexing
  col -= 1; // subtract 1 to convert to 0-based indexing

  // Checking if prior_grid is valid
  if (!check_prior_grid_validity(prior_grid)) {
    stop("Invalid prior_grid input. The sum of all probabilities must be 1.");
  }

  // Checking pod_grid is valid
  if (!check_pod_grid_validity(pod_grid)) {
    stop("Invalid pod_grid input. All elements must be greater than 0 and less than 1.");
  }

  // Checking number of rows and columns are equal for pior and pod
  if (prior_grid.nrow() != pod_grid.nrow() || prior_grid.ncol() != pod_grid.ncol()) {
    stop("Dimensions of prior_grid and pod_grid do not match.");
  }

  // Checking grid square co-ords exist within the prior matrix
  if (row < 0 || row >= prior_grid.nrow() || col < 0 || col >= prior_grid.ncol()) {
    stop("Invalid grid square coordinates.");
  }

  // Calculate the denominator for normalization. This is 1 - p*d (p=prior prob, d = prob of detection)
  double denom = 1.0 - prior_grid(row, col) * pod_grid(row, col);

  // Update the posterior probabilities
  NumericMatrix posterior_grid = clone(prior_grid); // Duplicating prior_grid input
  for (int i = 0; i < prior_grid.nrow(); ++i) {
    for (int j = 0; j < prior_grid.ncol(); ++j) {
      if (i == row && j == col) {
        posterior_grid(i, j) = prior_grid(i, j) * (1.0 - pod_grid(i, j)) / denom; // In given co-ords posterior prob = (p(1-p)/(1-pd))
      } else {
        posterior_grid(i, j) = prior_grid(i, j) / denom; // Else posterior prob  = p/(1-pd)
      }
    }
  }
  // Assigning "posterior" attribute
  posterior_grid.attr("type") = "posterior";

  return posterior_grid;
}
