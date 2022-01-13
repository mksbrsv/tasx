#include <fmt/color.h>

#include <algorithm>
#include <cctype>
#include <typeinfo>

#include "../include/group.h"
#include "../include/input_parser.h"
#include "../include/output.h"
#include "../include/todos.h"
#include "fmt/ranges.h"

int main(int argc, char** argv) {
  input_parser input(argc, argv);
  todo_groups groups;
  try {
    groups.init();
  } catch (std::logic_error& ex) {
    fmt::print(fg(fmt::terminal_color::red) | fmt::emphasis::bold, "ERROR:");
    fmt::print("{}", ex.what());
  }

  if (input.exist("-help")) {
    fmt::print("{}", utils::HELP);

  } else if (input.exist("-list")) {
    fmt::print(fmt::emphasis::bold, "{}", "Tasks:\n");
    if (input.exist("-hidden")) {
      for (int i = 0; i < groups.amount(); i++) {
        fmt::print(fmt::emphasis::bold | fmt::emphasis::underline |
                       fg(fmt::terminal_color::bright_black),
                   "@{}\n", groups[i].name);
        if (groups[i].list.empty()) continue;
        auto list_hidden = groups[i].list.get_list_without_done();
        for (int j = 0; j < list_hidden.size(); j++) {
          std::string id = fmt::format(fg(fmt::terminal_color::bright_black),
                                       "  {}.", list_hidden[j].get_id());
          std::string item;
          output::choose_priority(list_hidden[j], item);
          fmt::print("{} {}", id, item);
        }
      }
    } else {
      for (int i = 0; i < groups.amount(); i++) {
        fmt::print(fmt::emphasis::bold | fmt::emphasis::underline |
                       fg(fmt::terminal_color::bright_black),
                   "@{}\n", groups[i].name);
        if (groups[i].list.empty()) continue;
        for (int j = 0; j < groups[i].list.amount(); j++) {
          std::string id = fmt::format(fg(fmt::terminal_color::bright_black),
                                       "  {}.", groups[i].list[j].get_id());
          std::string item;
          output::choose_priority(groups[i].list[j], item);
          fmt::print("{} {}", id, item);
        }
      }
      fmt::print("\n{}", output::stats(groups));  // TODO: fix stats
    }
    //
    //
    // done, add, delete, clear, pr, edit, undo, do
    // done - 2 args - gi ti
    // add - 2 args - gi s
    // delete - 2 args - gi ti
    // clear - 1 arg opt - gi
    // pr - 3 args - gi ti s - [0] - c [1] - gi
    // edit 3 args - gi ti s
    // undo - 2 args - gi ti
    // do - 2 args - gi ti
    // if tok[1] does not contain word beginning with @ - group = board
    // if tok[0] is not add and clear - get tok[2] as id
    // if tok[0] is edit or pr - get subject
    //

  } else if (input.exist("-done")) {  // format: tasx done @group_name todo_id
    auto [group_name, todo_id, subject] = input.parse_args();
    auto [ec, msg] = groups[group_name].list.set_status(todo_id, status::done);
    if (static_cast<bool>(ec)) {
      fmt::print(fg(fmt::terminal_color::green), "\n{}",
                 "Status updated successfully");
    } else {
      fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
    }
  } else if (input.exist(
                 "-add")) {  // format: tasx add @group_name todo_subject
    if (input.exist("-group")) {
      auto [group_name, todo_id, subject] = input.parse_args();
      groups.add_group(subject);
      fmt::print(fg(fmt::terminal_color::green), "\n{}",
                 "Group added successfully");
    } else {
      auto [group_name, todo_id, subject] = input.parse_args();
      auto [ec, msg] = groups[group_name].list.add_todo(subject);
      if (static_cast<bool>(ec)) {
        fmt::print(fg(fmt::terminal_color::green), "\n{}",
                   "Task added successfully");
      } else {
        fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
      }
    }
  } else if (input.exist("-delete")) {
    if (input.exist("-group")) {
      auto [group_name, todo_id, subject] = input.parse_args();
      groups.remove_group(subject);
    } else {
      auto [group_name, todo_id, subject] = input.parse_args();
      auto [ec, msg] = groups[group_name].list.remove_todo(todo_id);
      if (static_cast<bool>(ec)) {
        fmt::print(fg(fmt::terminal_color::green), "\n{}",
                   "Task removed successfully");
      } else {
        fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
      }
    }
    //
  } else if (input.exist("-clear")) {
    auto [group_name, todo_id, subject] = input.parse_args();
    groups[group_name].list.clear();
    fmt::print(fg(fmt::terminal_color::green),
               "\nGroup @{} cleared successfully", group_name);

  } else if (input.exist("-pr")) {
    auto [group_name, todo_id, subject] = input.parse_args();
    auto [ec, msg] = groups[group_name].list.set_priority(
        todo_id, priority(std::stoi(subject)));
    if (static_cast<bool>(ec)) {
      fmt::print(fg(fmt::terminal_color::green), "\n{}",
                 "Priority updated successfully");
    } else {
      fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
    }

  } else if (input.exist("-do")) {
    auto [group_name, todo_id, subject] = input.parse_args();
    auto [ec, msg] =
        groups[group_name].list.set_status(todo_id, status::in_process);
    if (static_cast<bool>(ec)) {
      fmt::print(fg(fmt::terminal_color::green), "\n{}",
                 "Status updated successfully");
    } else {
      fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
    }
  } else if (input.exist("-undo")) {
    auto [group_name, todo_id, subject] = input.parse_args();
    auto [ec, msg] = groups[group_name].list.set_status(todo_id, status::todo);
    if (static_cast<bool>(ec)) {
      fmt::print(fg(fmt::terminal_color::green), "\n{}",
                 "Status updated successfully");
    } else {
      fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
    }
  } else if (input.exist("-edit")) {
    auto [group_name, todo_id, subject] = input.parse_args();
    auto [ec, msg] = groups[group_name].list.edit_todo(todo_id, subject);
    if (static_cast<bool>(ec)) {
      fmt::print(fg(fmt::terminal_color::green), "\n{}",
                 "Task edited successfully");
    } else {
      fmt::print(fg(fmt::terminal_color::red), "\nERROR: {}", msg);
    }

  } else {
    fmt::print("{}", output::stats(groups));
  }
  for (int i = 0; i < groups.amount(); i++) {
    if (groups[i].list.check_tasks()) {
      groups[i].list.clear();
    }
  }
  try {
    groups.close();
  } catch (std::logic_error& ex) {
    fmt::print(fg(fmt::terminal_color::red) | fmt::emphasis::bold, "ERROR:");
    fmt::print("{}", ex.what());
  }
}
