#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

struct return_t {
  explicit return_t(std::string gn = "Board", std::string s = "", int id = -1)
      : group_name(gn), id(id), subject(s) {}
  std::string group_name;
  int id;
  std::string subject;
};

class input_parser {
 public:
  input_parser(int argc, char** argv) noexcept;
  bool exist(const std::string& command) const;
  const std::string& get(const std::string& command) /* const */;
  std::tuple<std::string, int, std::string> parse(const std::string& command);
  std::tuple<std::string, std::string> parse_2arg(const std::string& command);
  return_t parse_args() const;

 private:
  std::vector<std::string> m_tokens;
  std::string sentence;
};

#endif  // INPUT_PARSER_H
