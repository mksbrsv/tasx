#include <algorithm>

#include "../include/input_parser.h"
#include "../include/todos.h"
#include "fmt/ranges.h"

int main(int argc, char **argv) {
  input_parser input(argc, argv);
  todo_list todos;
  todos.load_list();
  if (input.exist("--help") || input.exist("-h")) {
    fmt::print("{}", utils::HELP);
  }
  if (input.exist("--list") || input.exist("-l")) {
    for (int i = 0; i < todos.get_list().size(); i++) {
      fmt::print("{}", todos.get_list()[i]);
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
  todos.save_list();
}
