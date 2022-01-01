#ifndef TODOS_H
#define TODOS_H

#include <algorithm>
#include <fstream>
#include <iomanip>
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
  void edit_todo(const int index, const std::string &subject);
  void remove_todo(const int index);
  void set_priority(const int index, priority pr);
  void set_status(const int index, status st);
  void clear();
  todo_item &get_by_id(const int index);
  bool is_no_tasks_todo() const;
  const std::vector<todo_item> &get_list() const;
  const std::vector<todo_item> get_list_without_done() const;

 private:
  std::vector<todo_item> m_todos;
};

#endif
