#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iomanip>
#include <iostream>
#include <vector>

using std::istringstream;
using std::string;
using std::vector;

const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string& s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string& s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string& s) { return rtrim(ltrim(s)); }

vector<string> split(const string& s, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(s);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

#endif
