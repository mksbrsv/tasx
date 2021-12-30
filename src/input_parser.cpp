#include "../include/input_parser.h"

input_parser::input_parser(int argc, char** argv) noexcept {
  for (int i = 1; i < argc; i++) {
    this->m_tokens.push_back(std::string(argv[i]));
  }
}

bool input_parser::exist(const std::string& command) const {
  return std::find(this->m_tokens.begin(), this->m_tokens.end(), command) !=
         this->m_tokens.end();
}

const std::string& input_parser::get(const std::string& command) const {
  std::vector<std::string>::const_iterator it =
      std::find(this->m_tokens.begin(), this->m_tokens.end(), command);
  if (it != this->m_tokens.end() && ++it != this->m_tokens.end()) return *it;
  return this->empty_string;
}
