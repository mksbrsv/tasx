#include <algorithm>

#include "../include/input_parser.h"
#include "../include/todos.h"
#include "fmt/ranges.h"

int main(int argc, char **argv) {
  input_parser input(argc, argv);
  todo_list todos;
  todos.load_list();
  if (input.exist("-l")) {
    for (int i = 0; i < todos.get_list().size(); i++) {
      fmt::print("{}", todos.get_list()[i]);
    }
  }
}
