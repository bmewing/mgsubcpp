// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
#include <string>
#include <regex>

using namespace Rcpp;

// [[Rcpp::export]]
std::string rcpp_mgsub(std::string string, std::vector<std::string> const& match, std::vector<std::string> const& replace, bool const& ic) {
  std::string newString = "";
  std::smatch matches;
  std::string prefix = string;
  std::string detected;
  std::string suffix;

  std::regex::flag_type flags;
  flags |= std::regex_constants::optimize;
  if(ic) flags |= std::regex_constants::icase;

  std::vector<std::regex> r(match.size());
  std::transform(match.begin(), match.end(), r.begin(),
                 [&flags](std::string m) {return std::regex (m, flags);});

  int j=0;
  while(string.size() > 0){
    prefix = string;
    detected = "";
    suffix = "";
    j = 0;
    for(int i=0;i < match.size();i++){
      if (std::regex_search(string,matches, r[i])) {
        std::string pr = matches.prefix();
        std::string m = matches[0];
        if(pr.size() < prefix.size() || (pr.size() == prefix.size() && m.size() > detected.size())){
          prefix = pr;
          detected = m;
          suffix = matches.suffix();
          j=i;
        }
      }
    }
    if(prefix == string){
      newString = newString+string;
      string = "";
    } else {
      newString = newString+prefix+std::regex_replace(detected,r[j],replace[j],std::regex_constants::format_sed);
      string = suffix;
    }
  }
  return newString;
}
