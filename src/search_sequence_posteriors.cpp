#include <Rcpp.h>
using namespace Rcpp;


// Check if the sum of all elements of prior_grid is eqaul to 1
bool check_prior_grid_validity_ssq(NumericMatrix prior_grid) {
  double sum = 0;
  for (int r = 0; r < prior_grid.nrow(); ++r) {
    for (int c = 0; c < prior_grid.ncol(); ++c) {
      sum += prior_grid(r, c);
    }
  }
  return (abs(sum - 1) < 1e-6); // Allow for a small numerical error
}

// Check if all elements of the pod_grid matrix are greater than 0 and less than 1
bool check_pod_grid_validity_ssq(NumericMatrix pod_grid) {
  for (int r = 0; r < pod_grid.nrow(); ++r) {
    for (int c = 0; c < pod_grid.ncol(); ++c) {
      if (pod_grid(r, c) <= 0 || pod_grid(r, c) >= 1) {
        return false;
      }
    }
  }
  return true;
}

NumericMatrix update_posterior_neg_ssq(NumericMatrix prior_grid, NumericMatrix pod_grid, int row, int col) {
  // Checking if prior_grid is valid
  if (!check_prior_grid_validity_ssq(prior_grid)) {
    stop("Invalid prior_grid input. The sum of all probabilities must be 1.");
  }

  // Checking pod_grid is valid
  if (!check_pod_grid_validity_ssq(pod_grid)) {
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

//' Posteriors of a search list
//'
//' @description Calculates the posteriors for each step in a given search sequence.
//'
//' @details This function will calculate the posteriors and overall probability of detection for each step in a given search sequence matrix.
//' The function assumes a negative search result after each step.
//'
//' @param prior_grid A numeric matrix that is a valid probability density function. Use \code{\link{create_prior_grid}} for validation.
//'
//' @param pod_grid A numeric matrix. All matrix entries must be greater than 0 and less than 1.
//'
//' @param search_sequence An integer matrix with two columns. Each row represents the square to be searched. Column 1 is the row index
//' and column 2 is the column index. See example for more detail.
//'
//' @returns List of the same length as the search sequence. Each list element contains a posterior (Numeric Matrix), overall probability
//' of detection (Double) and the grid square searched (String)
//'
//' @examples
//' generate_sample_matrix(5)
//' search_sequence <- matrix(c(1,5,2,5,3,5,4,5,5,5), nrow = 5, ncol = 2)
//' search_sequence_posteriors(prior_grid, pod_grid, search_sequence)
//'
//' @export
// [[Rcpp::export]]
List search_sequence_posteriors(NumericMatrix prior_grid, NumericMatrix pod_grid, IntegerMatrix search_sequence) {
  // Checking if prior_grid is valid
  if (!check_prior_grid_validity_ssq(prior_grid)) {
    stop("Invalid prior_grid input. The sum of all probabilities must be 1.");
  }

  // Checking pod_grid is valid
  if (!check_pod_grid_validity_ssq(pod_grid)) {
    stop("Invalid pod_grid input. All elements must be greater than 0 and less than 1.");
  }

  // Checking number of rows and columns are equal for pior and pod
  if (prior_grid.nrow() != pod_grid.nrow() || prior_grid.ncol() != pod_grid.ncol()) {
    stop("Dimensions of prior_grid and pod_grid do not match.");
  }

  // Checking the search matrix contains 2 columns
  if (search_sequence.ncol() != 2) {
    stop("Search sequence matrix must have 2 columns.");
  }

  // Declaring variables
  int num_searches = search_sequence.nrow(); // Number of searches, no of search matrix rows
  List search_posteriors(num_searches); // List for output
  NumericMatrix current_posterior = clone(prior_grid); // Duplicating prior input

  // Searching the matrix of grid squares
  for (int i = 0; i < num_searches; ++i) {
    int row = search_sequence(i, 0) - 1; // Adjust for 0-based indexing
    int col = search_sequence(i, 1) - 1; // Adjust for 0-based indexing

    // Checking grid square co-ords exist within the prior matrix
    if (row < 0 || row >= prior_grid.nrow() || col < 0 || col >= prior_grid.ncol()) {
      stop("Invalid grid square coordinates in search sequence.");
    }

    // Update the posterior probabilities using the "update_posterior_neg" function
    current_posterior = update_posterior_neg_ssq(current_posterior, pod_grid, row, col);

    // Calculate the overall probability of finding the object
    double prob = 0.0;
    for (int r = 0; r < prior_grid.nrow(); ++r) {
      for (int c = 0; c < prior_grid.ncol(); ++c) {
        prob += current_posterior(r, c) * pod_grid(r, c); // Sum of the prior prob * pod for the whole grid
      }
    }

    // Creating list for output
    List search_result = List::create(
      _["posterior"] = current_posterior, // Posterior matrix
      _["searched_square"] = search_sequence.row(i), // Searched grid square
      _["overall_detection"] = prob // Overall detection probability for current posterior
    );
    search_posteriors[i] = search_result; // Assigning to list output
  }

  return search_posteriors;
}
