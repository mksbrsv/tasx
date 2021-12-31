#include <algorithm>
#include <sstream>

#include "../include/input_parser.h"
#include "../include/output.h"
#include "../include/todos.h"
#include "fmt/ranges.h"

int main(int argc, char** argv) {
  input_parser input(argc, argv);
  todo_list todos;
  todos.load_list();
  if (input.exist("--help") || input.exist("-h")) {
    fmt::print("{}", utils::HELP);
  }
  if (input.exist("--list") || input.exist("-l")) {
    for (int i = 0; i < todos.get_list().size(); i++) {
      std::string id =
          fmt::format(fg(fmt::terminal_color::bright_black), "{}.", i);
      std::string item = output::low_priority(todos.get_list()[i]);
      output::choose_priority(todos.get_list()[i], item);
      fmt::print("{} {}", id, item);
    }
  }
  if (input.exist("--done") || input.exist("-d")) {
    auto done_id = input.get(input.exist("-d") ? "-d" : "--done");
    todos.done(std::stoi(done_id));
  }
  if (input.exist("--new") || input.exist("-n")) {
    auto new_todo = input.get(input.exist("-n") ? "-n" : "--new");
    todos.add_todo(new_todo);
  }
  if (input.exist("--remove") || input.exist("-r")) {
    auto remove_id = input.get(input.exist("-r") ? "-r" : "--remove");
    todos.remove_todo(std::stoi(remove_id));
  }
  if (input.exist("--clear") || input.exist("-c")) {
    todos.clear();
  }
  if (input.exist("--priority") || input.exist("-p")) {
    auto command = input.get(input.exist("-p") ? "-p" : "--priority");
    auto it = command.find(" ");
    auto todo_id = command.substr(0, it);
    auto pr = command.substr(it + 1, command.length() - 1);

    todos.set_priority(std::stoi(todo_id), priority(std::stoi(pr)));
  }
  // if (input.exist("-t")) {
  //   output::colors();
  // }

  todos.save_list();
}
