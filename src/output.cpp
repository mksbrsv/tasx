#include "../include/output.h"

namespace output {
void choose_priority(const todo_item& item, std::string& formatted_string) {
  if (item.get_status() == status::done) {
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
  if (item.get_status() == status::done) {
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

std::tuple<int, int, int, int> calc_stats(const todo_list& list) {
  int done = 0;
  int todo = 0;
  int in_process = 0;
  int progress = 0;
  for (auto& ti : list.get_list()) {
    if (ti.get_status() == status::done)
      done++;
    else if (ti.get_status() == status::in_process)
      in_process++;
    else
      todo++;
  }
  progress = (done * 100) / (todo + done + in_process);
  return {done, todo, in_process, progress};
}

std::string stats(const todo_list& list) {
  auto [done, todo, in_process, progress] = output::calc_stats(list);
  std::string done_str =
      fmt::format(fg(fmt::terminal_color::green), "{}", done);
  std::string todo_str =
      fmt::format(fg(fmt::terminal_color::magenta), "{}", todo);
  std::string in_process_str =
      fmt::format(fg(fmt::terminal_color::cyan), "{}", in_process);
  std::string progress_str =
      fmt::format(fg(fmt::terminal_color::blue), "{}%", progress);
  std::string stats;
  if (done == list.get_list().size())
    stats = fmt::format(fg(fmt::terminal_color::blue), "  {}",
                        "All tasks done. It's time to cheer yourself up");
  else if (done + todo + in_process == 0)
    stats = fmt::format(fg(fmt::terminal_color::blue), "  {}",
                        "No tasks. It's time to make something");
  else
    stats = fmt::format(
        "  {} of tasks complete\n  {} done  {} pending  {} in process",
        progress_str, done_str, todo_str, in_process_str);
  return stats;
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
