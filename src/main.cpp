#include <algorithm>
#include <cctype>

#include "../include/input_parser.h"
#include "../include/output.h"
#include "../include/todos.h"
#include "fmt/ranges.h"

/*
 * TODO: fix clear arg
 * */

int main(int argc, char** argv) {
  input_parser input(argc, argv);
  todo_list todos;
  todos.load_list();

  if (input.exist("--help") || input.exist("-h")) {
    fmt::print("{}", utils::HELP);

  } else if (input.exist("--list") || input.exist("-l")) {
    fmt::print(fmt::emphasis::bold, "{}", "Tasks:\n");
    if (input.exist("--hidden") || input.exist("-hd")) {
      auto list_hidden = todos.get_list_without_done();
      for (int i = 0; i < list_hidden.size(); i++) {
        std::string id =
            fmt::format(fg(fmt::terminal_color::bright_black), "  {}.", i);
        std::string item = output::low_priority(list_hidden[i]);
        output::choose_priority(list_hidden[i], item);
        fmt::print("{} {}", id, item);
      }
    } else {
      for (int i = 0; i < todos.get_list().size(); i++) {
        std::string id =
            fmt::format(fg(fmt::terminal_color::bright_black), "  {}.", i);
        std::string item = output::low_priority(todos.get_list()[i]);
        output::choose_priority(todos.get_list()[i], item);
        fmt::print("{} {}", id, item);
      }
    }
    fmt::print("\n{}", output::stats(todos));

  } else if (input.exist("--done") || input.exist("-d")) {
    auto done_id = input.get(input.exist("-d") ? "-d" : "--done");
    todos.set_status(std::stoi(done_id), status::done);

  } else if (input.exist("--new") || input.exist("-n")) {
    auto new_todo = input.get(input.exist("-n") ? "-n" : "--new");
    todos.add_todo(new_todo);

  } else if (input.exist("--remove") || input.exist("-r")) {
    auto remove_id = input.get(input.exist("-r") ? "-r" : "--remove");
    todos.remove_todo(std::stoi(remove_id));

  } else if (input.exist("--clear") || input.exist("-c")) {
    todos.clear();

  } else if (input.exist("--priority") || input.exist("-p")) {
    auto command = input.get(input.exist("-p") ? "-p" : "--priority");
    auto it = command.find(" ");
    auto todo_id = command.substr(0, it);
    auto pr = command.substr(it + 1, command.length() - 1);
    todos.set_priority(std::stoi(todo_id), priority(std::stoi(pr)));

  } else if (input.exist("--go") || input.exist("-g")) {
    auto todo_it = input.get(input.exist("-g") ? "-g" : "--go");
    todos.set_status(std::stoi(todo_it), status::in_process);

  } else if (input.exist("--edit") || input.exist("-e")) {
    auto command = input.get(input.exist("-e") ? "-e" : "--edit");
    auto it = command.find(" ");
    auto todo_id = command.substr(0, it);
    auto subject = command.substr(it + 1, command.length() - 1);
    todos.edit_todo(std::stoi(todo_id), subject);

  } else {
    fmt::print("{}", output::stats(todos));
  }
  if (todos.is_no_tasks_todo()) todos.clear();

  todos.save_list();
}
