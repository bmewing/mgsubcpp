#' Takes a list of conversions and applies it simultaneously to a string
#'
#' @param string a character vector where replacements are sought
#' @param conversions named list of conversions to apply
#' @param ignore.case logical flag to ignore case when matching
#' @return Converted string.
#' @examples
#' mgsub("hey, ho",list("hey"="ho","ho"="hey"))
#' mgsub("developer",list("e" ="p", "p" = "e"))
#' mgsub("The chemical Dopaziamine is fake",
#'       list("dopa(.*?) "="mega\\1 ","fake"="real"),
#'       ignore.case=TRUE)
#' @export

mgsub = function(string,conversions=list(),ignore.case=FALSE){
  mgsubcpp::rcpp_mgsub(string,names(conversions),unlist(conversions),ignore.case)
}
