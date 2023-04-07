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
//' @param prior_input A numeric matrix
//' @export
// [[Rcpp::export]]
NumericMatrix create_prior_grid(NumericMatrix prior_input) {
  // Normalizing matrix t create a valid PDF
  NumericMatrix prior_grid = normalize_matrix(prior_input);

  // Assigning "prior" attribute to matrix
  prior_grid.attr("type") = "prior";

  return prior_grid;
}
