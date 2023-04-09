#include <Rcpp.h>
using namespace Rcpp;
//' Melt Search sequence output
//'
//' @description Melt the output of search sequence functions into long data-frame format
//'
//' @details This function melts the output of a search function to a long data-frame format to allow for easier analysis
//' of the searcg
//'
//' @param search_posteriors, the list output of a search function
//'
//' @returns A dataframe
//'
//' @examples
//' generate_sample_matrix(5)
//' search_sequence <- matrix(c(1,5,2,5,3,5,4,5,5,5), nrow = 5, ncol = 2)
//' search_posteriors <- search_sequence_posteriors(prior_grid, pod_grid, search_sequence)
//' posterior_sequence_long(search_posteriors)
//'
//' @export
// [[Rcpp::export]]
DataFrame posterior_sequence_long(List search_posteriors) {
  // Declare variables
  int num_searches = search_posteriors.size(); // Number of searches completed
  std::vector<int> var1, var2, search_id; // Vectors of var1(y co-ord), var2(x co-ord) and search id
  std::vector<std::string> searched_square; // String vector of searched square e.g "(2,5)"
  std::vector<double> p, overall_detection; // Detection probability


  for (int i = 0; i < num_searches; ++i) {
    // Accessing list elements for each search
    List search_result = search_posteriors[i]; // Extracting list "i"
    NumericMatrix posterior = search_result["posterior"]; // Posterior matrix
    IntegerVector searched_sq = search_result["searched_square"]; // Searched sqaure
    double detection = search_result["overall_detection"]; // Detection prob

    // Declare variables
    int rows = posterior.nrow(); // No. of rows of posterior
    int cols = posterior.ncol(); // No. of cols of posterior

    // Melt function. Assigning vars to each (var1,var2) co-ord pair
    for (int r = 1; r <= rows; ++r) {
      for (int c = 1; c <= cols; ++c) {
        var1.push_back(r); // var1 (y)
        var2.push_back(c); // var2 (x)
        p.push_back(posterior(r - 1, c - 1)); // Posterior prob
        search_id.push_back(i + 1); // Search Id
        searched_square.push_back(std::to_string(searched_sq[0]) + "," + std::to_string(searched_sq[1])); // Searched square string
        overall_detection.push_back(detection); // Detection prob
      }
    }
  }

  // Create data frame out of vectors
  DataFrame result = DataFrame::create(
    _["Var1"] = var1,
    _["Var2"] = var2,
    _["p"] = p,
    _["searched_square"] = searched_square,
    _["overall_detection"] = overall_detection,
    _["search_id"] = search_id
  );

  return result;
}
