#include <Rcpp.h>
using namespace Rcpp;

NumericMatrix normalize_matrix(NumericMatrix mat) {
  // Normalize the matrix so that the sum of all elements is equal to one

  // Declaring variables
  double sum = 0.0; // Initial sum
  int n_rows = mat.nrow(); // Number of matrix rows
  int n_cols = mat.ncol(); // Number of matrix columns

  // Summing all matrix elements
  for (int i = 0; i < n_rows; ++i) {
    for (int j = 0; j < n_cols; ++j) {
      sum += mat(i, j);
    }
  }

  // Dividing all matrix elements by the sum
  for (int i = 0; i < n_rows; ++i) {
    for (int j = 0; j < n_cols; ++j) {
      mat(i, j) /= sum;
    }
  }

  return mat;
}



//' Create a prior grid
//'
//' @description 'create_prior_grid' returns a valid prior from a given numeric matrix
//'
//' @details This is a function that takes any numeric matrix and returns another numeric matrix which is a valid probability
//' density function that has a "prior" attribute assigned to it. The input doesn't have to be a valid PDF the function will
//' do this so when using this package its always good to use this function before using any of the search functions.
//'
//' @param prior_input A numeric matrix
//'
//' @returns A (normalized) numeric matrix
//'
//' @examples create_prior_grid(matrix(c(1,2,3,4),nrow = 1, ncol = 4))
//'
//'
//' @export
// [[Rcpp::export]]
NumericMatrix create_prior_grid(NumericMatrix prior_input) {
  // Normalizing matrix t create a valid PDF
  NumericMatrix prior_grid = normalize_matrix(prior_input);

  // Assigning "prior" attribute to matrix
  prior_grid.attr("type") = "prior";

  return prior_grid;
}
