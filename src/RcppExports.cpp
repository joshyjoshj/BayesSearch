// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// create_prior_grid
NumericMatrix create_prior_grid(NumericMatrix prior_input);
RcppExport SEXP _BayesSearch_create_prior_grid(SEXP prior_inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type prior_input(prior_inputSEXP);
    rcpp_result_gen = Rcpp::wrap(create_prior_grid(prior_input));
    return rcpp_result_gen;
END_RCPP
}
// search_sequence_posteriors
List search_sequence_posteriors(NumericMatrix prior_grid, NumericMatrix pod_grid, IntegerMatrix search_sequence);
RcppExport SEXP _BayesSearch_search_sequence_posteriors(SEXP prior_gridSEXP, SEXP pod_gridSEXP, SEXP search_sequenceSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type prior_grid(prior_gridSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type pod_grid(pod_gridSEXP);
    Rcpp::traits::input_parameter< IntegerMatrix >::type search_sequence(search_sequenceSEXP);
    rcpp_result_gen = Rcpp::wrap(search_sequence_posteriors(prior_grid, pod_grid, search_sequence));
    return rcpp_result_gen;
END_RCPP
}
// update_posterior_neg
NumericMatrix update_posterior_neg(NumericMatrix prior_grid, NumericMatrix pod_grid, int row, int col);
RcppExport SEXP _BayesSearch_update_posterior_neg(SEXP prior_gridSEXP, SEXP pod_gridSEXP, SEXP rowSEXP, SEXP colSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type prior_grid(prior_gridSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type pod_grid(pod_gridSEXP);
    Rcpp::traits::input_parameter< int >::type row(rowSEXP);
    Rcpp::traits::input_parameter< int >::type col(colSEXP);
    rcpp_result_gen = Rcpp::wrap(update_posterior_neg(prior_grid, pod_grid, row, col));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_BayesSearch_create_prior_grid", (DL_FUNC) &_BayesSearch_create_prior_grid, 1},
    {"_BayesSearch_search_sequence_posteriors", (DL_FUNC) &_BayesSearch_search_sequence_posteriors, 3},
    {"_BayesSearch_update_posterior_neg", (DL_FUNC) &_BayesSearch_update_posterior_neg, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_BayesSearch(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
