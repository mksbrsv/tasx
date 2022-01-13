#include "../include/input_parser.h"

#include <functional>
#include <iostream>
#include <numeric>
#include <string>

input_parser::input_parser(int argc, char** argv) noexcept {
  for (int i = 1; i < argc; i++) {
    this->m_tokens.push_back(std::string(argv[i]));
  }
}

bool input_parser::exist(const std::string& command) const {
  return std::find(this->m_tokens.begin(), this->m_tokens.end(), command) !=
         this->m_tokens.end();
}

const std::string& input_parser::get(const std::string& command) /* const */ {
  std::vector<std::string>::const_iterator it =
      std::find(this->m_tokens.begin(), this->m_tokens.end(), command);
  if (it != this->m_tokens.end()) {
    while (++it != this->m_tokens.end()) {
      this->sentence = this->sentence + *it + " ";
    }
  }
  return this->sentence;
}

std::tuple<std::string, std::string> input_parser::parse_2arg(
    const std::string& command) {
  auto space = [](std::string a, std::string b) -> std::string {
    if (a == b) return std::move(a);
    return std::move(a) + ' ' + std::move(b);
  };

  auto is_contain_group = [this]() -> bool {
    for (auto& token : m_tokens) {
      if (token.find("@") != std::string::npos) return true;
    }
    return false;
  };
  if (!is_contain_group())
    return std::make_tuple("board",
                           std::accumulate(m_tokens.begin() + 1, m_tokens.end(),
                                           m_tokens[1], space));
  return std::make_tuple(m_tokens[1],
                         std::accumulate(m_tokens.begin() + 2, m_tokens.end(),
                                         m_tokens[2], space));
}

std::tuple<std::string, int, std::string> input_parser::parse(
    const std::string& command) {
  auto space = [](std::string a, std::string b) -> std::string {
    return std::move(a) + ' ' + std::move(b);
  };
  if (m_tokens.size() == 3)
    return std::make_tuple(m_tokens[1].erase(0, 1), std::stoi(m_tokens[2]),
                           m_tokens[1]);
  if (m_tokens.size() == 4)
    return std::make_tuple(m_tokens[1].erase(0, 1), std::stoi(m_tokens[2]),
                           m_tokens[3]);
  if (m_tokens.size() > 4) {
    std::string s = std::accumulate(m_tokens.begin() + 3, m_tokens.end(),
                                    m_tokens[3],  // start with first element
                                    space);

    return std::make_tuple(m_tokens[1].erase(0, 1), std::stoi(m_tokens[2]), s);
  }
  return {"", 0, ""};
}

return_t input_parser::parse_args()
    const {  // TODO: add support default group for all commands
  auto space = [](std::string a, std::string b) -> std::string {
    if (a == b) return std::move(a);
    return std::move(a) + ' ' + std::move(b);
  };
  std::string group_name = "Board";
  int id = -1;
  std::string subject = "";
  if (m_tokens[1] == "-group") {
    return return_t(group_name, m_tokens[2], id);
  }
  if (m_tokens[1].find("@") != std::string::npos) {
    group_name = m_tokens[1];
    group_name.erase(0, 1);
  }
  if (m_tokens[0] != "-add" && m_tokens[0] != "-clear") {
    if (group_name == "Board") {
      id = std::stoi(m_tokens[1]);
      if (m_tokens[0] == "-edit" || m_tokens[0] == "-pr") {
        subject = std::accumulate(m_tokens.begin() + 2, m_tokens.end(),
                                  m_tokens[2],  // start with first element
                                  space);
      }
    } else {
      id = std::stoi(m_tokens[2]);
      if (m_tokens[0] == "-edit" || m_tokens[0] == "-pr") {
        subject = std::accumulate(m_tokens.begin() + 3, m_tokens.end(),
                                  m_tokens[3],  // start with first element
                                  space);
      }
    }
  }
  if (m_tokens[0] == "-add") {
    if (m_tokens[1].find("@") == std::string::npos) {
      subject = std::accumulate(m_tokens.begin() + 1, m_tokens.end(),
                                m_tokens[1],  // start with first element
                                space);
    } else {
      subject = std::accumulate(m_tokens.begin() + 2, m_tokens.end(),
                                m_tokens[2],  // start with first element
                                space);
    }
  }
  if (id == -1) {
    if (subject == "") {
      return return_t(group_name);
    }
    return return_t(group_name, subject);
  }
  return return_t(group_name, subject, id);
}
