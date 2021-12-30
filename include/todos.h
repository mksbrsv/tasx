#ifndef TODOS_H
#define TODOS_H

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>

#include "todo.h"
#include "utils.h"

class todo_list {
 public:
  todo_list() = default;
  ~todo_list() = default;
  void save_list(const std::string &file = utils::TASX_FILE);
  void load_list(const std::string &file = utils::TASX_FILE);
  void add_todo(const todo_item &todo);
  void add_todo(const std::string &subject);
  void remove_todo(const int index);
  void done(const int index);
  void clear();
  const std::vector<todo_item> get_list() const;

 private:
  std::vector<todo_item> m_todos;
};

#endif
