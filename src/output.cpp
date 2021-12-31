#include "../include/output.h"

namespace output {
void choose_priority(const todo_item& item, std::string& formatted_string) {
  if (item.get_status()) {
    done_todo(item, formatted_string);
    return;
  }
  auto pr = item.get_priority();
  switch (pr) {
    case priority::low: {
      break;
    }
    case priority::medium: {
      med_priority(item, formatted_string);
      break;
    }
    case priority::high: {
      high_priority(item, formatted_string);
      break;
    }
    case priority::critical: {
      critical_priority(item, formatted_string);
      break;
    }
    default: {
      break;
    }
  }
}

void done_todo(const todo_item& item, std::string& formatted_string) {
  if (item.get_status()) {
    formatted_string = fmt::format(
        fg(fmt::terminal_color::bright_black) | fmt::emphasis::strikethrough,
        "{}", item);
  }
}

std::string low_priority(const todo_item& item) {
  std::string formatted_string = fmt::format("{}", item);
  return formatted_string;
}

void med_priority(const todo_item& item, std::string& formatted_string) {
  formatted_string = fmt::format(fg(fmt::terminal_color::yellow), "{}", item);
}

void high_priority(const todo_item& item, std::string& formatted_string) {
  formatted_string = fmt::format(fg(fmt::terminal_color::red), "{}", item);
}

void critical_priority(const todo_item& item, std::string& formatted_string) {
  formatted_string = fmt::format(
      fg(fmt::terminal_color::red) | fmt::emphasis::bold, "{}", item);
}

// void colors() {
//   fmt::print(fg(fmt::terminal_color::black), "{}", "black\n");
//   fmt::print(fg(fmt::terminal_color::red), "{}", "red\n");
//   fmt::print(fg(fmt::terminal_color::green), "{}", "green\n");
//   fmt::print(fg(fmt::terminal_color::yellow), "{}", "yellow\n");
//   fmt::print(fg(fmt::terminal_color::blue), "{}", "blue\n");
//   fmt::print(fg(fmt::terminal_color::magenta), "{}", "magenta\n");
//   fmt::print(fg(fmt::terminal_color::cyan), "{}", "cyan\n");
//   fmt::print(fg(fmt::terminal_color::white), "{}", "white\n");
//   fmt::print(fg(fmt::terminal_color::bright_black), "{}", "br_black\n");
//   fmt::print(fg(fmt::terminal_color::bright_red), "{}", "br_red\n");
//   fmt::print(fg(fmt::terminal_color::bright_green), "{}", "br_green\n");
//   fmt::print(fg(fmt::terminal_color::bright_yellow), "{}", "br_yellow\n");
//   fmt::print(fg(fmt::terminal_color::bright_blue), "{}", "br_blue\n");
//   fmt::print(fg(fmt::terminal_color::bright_magenta), "{}", "br_magenta\n");
//   fmt::print(fg(fmt::terminal_color::bright_cyan), "{}", "br_cyan\n");
//   fmt::print(fg(fmt::terminal_color::bright_white), "{}", "br_white\n");
// }

}  // namespace output
