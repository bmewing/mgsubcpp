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
  auto flags = (ic ? std::regex_constants::icase | std::regex_constants::collate : std::regex_constants::collate);
  int j=0;
  while(string.size() > 0){
    prefix = string;
    detected = "";
    suffix = "";
    j = 0;
    for(int i=0;i < match.size();i++){
      std::regex r(match[i], flags);
      if (std::regex_search(string,matches, r)) {
        std::string pr = matches.prefix();
        std::string m = matches[0];
        if(pr.size() <= prefix.size()){
          if(pr.size() < prefix.size()){
            prefix = pr;
            detected = m;
            suffix = matches.suffix();
            j=i;
          } else {
            if(m.size() > detected.size()){
              prefix = pr;
              detected = m;
              suffix = matches.suffix();
              j=i;
            }
          }
        }
      }
    }
    if(prefix == string){
      newString = newString+string;
      string = "";
    } else {
      std::regex r(match[j], flags);
      newString = newString+prefix+std::regex_replace(detected,r,replace[j],std::regex_constants::format_sed);
      string = suffix;
    }
  }
  return newString;
}
