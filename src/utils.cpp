#include "../include/utils.h"

std::string utils::to_lower(std::string str) {
  std::string res = "";
  std::for_each(str.begin(), str.end(),
                [&res](char c) { res.push_back(::tolower(c)); });

  return res;
}

std::string utils::to_upper(std::string str) {
  std::string res = "";
  std::for_each(str.begin(), str.end(),
                [&res](char c) { res.push_back(::toupper(c)); });

  return res;
}
