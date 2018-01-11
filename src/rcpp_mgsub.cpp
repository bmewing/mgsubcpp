// [[Rcpp::plugins(cpp11)]]

#include <Rcpp.h>
#include <string>
#include <regex>

using namespace Rcpp;

// [[Rcpp::export]]
std::string rcpp_mgsub(std::string string, std::vector<std::string> match, std::vector<std::string> replace, bool ic) {
  std::string newString = "";
  std::smatch matches;
  std::string prefix = string;
  std::string detected = "";
  std::string suffix = "";
  std::regex r;
  std::regex r0;
  int j=0;
  while(string.size() > 0){
    prefix = string;
    detected = "";
    suffix = "";
    j = 0;
    for(int i=0;i < match.size();i++){
      std::regex rc(match[i], std::regex_constants::collate);
      std::regex ric(match[i], std::regex_constants::icase | std::regex_constants::collate);
      if(ic){
        r = ric;
      } else {
        r = rc;
      }
      if (std::regex_search(string,matches, r)) {
        std::string pr = matches.prefix();
        std::string m = matches[0];
        if(pr.size() <= prefix.size()){
          if(pr.size() < prefix.size()){
            prefix = pr;
            detected = m;
            suffix = matches.suffix();
            j=i;
            r0 = r;
          } else {
            if(m.size() > detected.size()){
              prefix = pr;
              detected = m;
              suffix = matches.suffix();
              j=i;
              r0 = r;
            }
          }
        }
      }
    }
    if(prefix == string){
      newString = newString+string;
      string = "";
    } else {
      newString = newString+prefix+std::regex_replace(detected,r0,replace[j],std::regex_constants::format_sed);
      string = suffix;
    }
  }
  return newString;
}
