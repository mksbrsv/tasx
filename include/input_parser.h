#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <algorithm>
#include <string>
#include <vector>

class input_parser {
 public:
  input_parser(int argc, char** argv) noexcept;
  bool exist(const std::string& command) const;
  const std::string& get(const std::string& command) const;

 private:
  std::vector<std::string> m_tokens;
  std::string empty_string;
};

#endif  // INPUT_PARSER_H
