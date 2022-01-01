#include <fmt/color.h>

#include <algorithm>
#include <cctype>

#include "../include/input_parser.h"
#include "../include/output.h"
#include "../include/todos.h"
#include "fmt/ranges.h"

int main(int argc, char** argv) {
  input_parser input(argc, argv);
  todo_list todos;
  try {
    todos.load_list();
  } catch (std::logic_error& ex) {
    fmt::print(fg(fmt::terminal_color::red) | fmt::emphasis::bold, "ERROR:");
    fmt::print("{}", ex.what());
  }

  if (input.exist("--help") || input.exist("-h")) {
    fmt::print("{}", utils::HELP);

  } else if (input.exist("list")) {
    fmt::print(fmt::emphasis::bold, "{}", "Tasks:\n");
    if (input.exist("hidden")) {
      auto list_hidden = todos.get_list_without_done();
      for (int i = 0; i < list_hidden.size(); i++) {
        std::string id = fmt::format(fg(fmt::terminal_color::bright_black),
                                     "  {}.", list_hidden[i].get_id());
        std::string item = output::low_priority(list_hidden[i]);
        output::choose_priority(list_hidden[i], item);
        fmt::print("{} {}", id, item);
      }
    } else {
      for (int i = 0; i < todos.get_list().size(); i++) {
        std::string id = fmt::format(fg(fmt::terminal_color::bright_black),
                                     "  {}.", todos.get_list()[i].get_id());
        std::string item = output::low_priority(todos.get_list()[i]);
        output::choose_priority(todos.get_list()[i], item);
        fmt::print("{} {}", id, item);
      }
    }
    fmt::print("\n{}", output::stats(todos));

  } else if (input.exist("done")) {
    auto done_id = input.get("done");
    todos.set_status(std::stoi(done_id), status::done);

  } else if (input.exist("add")) {
    auto new_todo = input.get("add");
    todos.add_todo(new_todo);

  } else if (input.exist("delete")) {
    auto remove_id = input.get("delete");
    todos.remove_todo(std::stoi(remove_id));

  } else if (input.exist("clear")) {
    todos.clear();

  } else if (input.exist("pr")) {
    auto command = input.get("pr");
    auto it = command.find(" ");
    auto todo_id = command.substr(0, it);
    auto pr = command.substr(it + 1, command.length() - 1);
    todos.set_priority(std::stoi(todo_id), priority(std::stoi(pr)));

  } else if (input.exist("do")) {
    auto todo_it = input.get("do");
    todos.set_status(std::stoi(todo_it), status::in_process);

  } else if (input.exist("edit")) {
    auto command = input.get("edit");
    auto it = command.find(" ");
    auto todo_id = command.substr(0, it);
    auto subject = command.substr(it + 1, command.length() - 1);
    todos.edit_todo(std::stoi(todo_id), subject);

  } else {
    fmt::print("{}", output::stats(todos));
  }
  if (todos.is_no_tasks_todo()) todos.clear();

  try {
    todos.save_list();
  } catch (std::logic_error& ex) {
    fmt::print(fg(fmt::terminal_color::red) | fmt::emphasis::bold, "ERROR:");
    fmt::print("{}", ex.what());
  }
}
