#include <Rcpp.h>
using namespace Rcpp;

// Check if the sum of all elements of prior_grid is eqaul to 1
bool check_prior_grid_validity_optim(NumericMatrix prior_grid) {
  double sum = 0;
  for (int r = 0; r < prior_grid.nrow(); ++r) {
    for (int c = 0; c < prior_grid.ncol(); ++c) {
      sum += prior_grid(r, c);
    }
  }
  return (abs(sum - 1) < 1e-6); // Allow for a small numerical error
}

// Check if all elements of the pod_grid matrix are greater than 0 and less than 1
bool check_pod_grid_validity_optim(NumericMatrix pod_grid) {
  for (int r = 0; r < pod_grid.nrow(); ++r) {
    for (int c = 0; c < pod_grid.ncol(); ++c) {
      if (pod_grid(r, c) <= 0 || pod_grid(r, c) >= 1) {
        return false;
      }
    }
  }
  return true;
}

NumericMatrix update_posterior_neg_optim(NumericMatrix prior_grid, NumericMatrix pod_grid, int row, int col) {
  // Checking if prior_grid is valid
  if (!check_prior_grid_validity_optim(prior_grid)) {
    stop("Invalid prior_grid input. The sum of all probabilities must be 1.");
  }

  // Checking pod_grid is valid
  if (!check_pod_grid_validity_optim(pod_grid)) {
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

//' Optimal search posteriors
//'
//' @description Calculates the posteriors of the optimal search of a given length
//'
//' @details This function takes a cost grid in addition to the standard prior grid and probability of detection grid and will calculate the optimal
//' search sequence for a given length.
//'
//' @param prior_grid A numeric matrix that is a valid probability density function. Use \code{\link{create_prior_grid}} for validation.
//'
//' @param pod_grid A numeric matrix. All matrix entries must be greater than 0 and less than 1.
//'
//' @param cost_grid A numeric matrix representing the cost of searching each grid square
//'
//' @param num_searches Integer representing the number of searches to perform
//'
//' @returns List of the same length as the search sequence. Each list element contains a posterior (Numeric Matrix), overall probability
//' of detection (Double) and the grid square searched (String)
//'
//' @examples
//'
//' generate_sample_matrix(5)
//' optimal_search_sequence_posteriors(prior_grid, pod_grid, cost_grid, 10)
//'
// [[Rcpp::export]]
List optimal_search_sequence_posteriors(NumericMatrix prior_grid, NumericMatrix pod_grid, NumericMatrix cost_grid, int num_searches) {
  // Checking if prior_grid is valid
  if (!check_prior_grid_validity_optim(prior_grid)) {
    stop("Invalid prior_grid input. The sum of all probabilities must be 1.");
  }

  // Checking pod_grid is valid
  if (!check_pod_grid_validity_optim(pod_grid)) {
    stop("Invalid pod_grid input. All elements must be greater than 0 and less than 1.");
  }

  // Declare variables
  List result; // Output list
  NumericMatrix current_prior = clone(prior_grid);// Duplicating prior

  // Searching num_searches
  for (int i = 0; i < num_searches; ++i) {
    // Declaring variables
    int rows = current_prior.nrow(); // No. prior rows
    int cols = current_prior.ncol(); // No. prior cols
    double max_value = -1; // Initial max value for comparison within loop
    IntegerVector optimal_square(2); // Vector to store searched square

    // Loop to calculate which grid square contains max value
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        double value = (current_prior(r, c) * pod_grid(r, c)) / cost_grid(r, c);
        if (value > max_value) {
          max_value = value;
          optimal_square[0] = r;
          optimal_square[1] = c;
        }
      }
    }

    // Calculating posterior using "update_posterior_neg"
    NumericMatrix posterior = update_posterior_neg_optim(current_prior, pod_grid, optimal_square[0], optimal_square[1]);

    // Calculate overall detection probability
    double overall_detection = 0;
    for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
        overall_detection += posterior(r, c) * pod_grid(r, c);
      }
    }

    // Create list
    List search_result = List::create(
      _["posterior"] = posterior,
      _["searched_square"] = optimal_square + 1,
      _["overall_detection"] = overall_detection
    );

    // Add list to results
    result.push_back(search_result);

    //Update prior
    current_prior = posterior;
  }
  return result;
}
