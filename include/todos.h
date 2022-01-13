#ifndef TODOS_H
#define TODOS_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <vector>

#include "todo.h"
#include "utils.h"

enum class error_code : bool { success = true, fail = false };

class todo_list {
 public:
  todo_list() noexcept;
  ~todo_list() = default;
  void save_list(nlohmann::json &j, const std::string &file = utils::TASX_FILE);
  void load_list(nlohmann::json &j, const std::string &file = utils::TASX_FILE);
  std::pair<error_code, std::string> add_todo(const todo_item &todo);
  std::pair<error_code, std::string> add_todo(const std::string &subject);
  std::pair<error_code, std::string> edit_todo(const int index,
                                               const std::string &subject);
  std::pair<error_code, std::string> remove_todo(const int index);
  std::pair<error_code, std::string> set_priority(const int index, priority pr);
  std::pair<error_code, std::string> set_status(const int index, status st);
  void clear();
  int amount() const;
  int get_id(const int index);
  todo_item &operator[](int i);
  todo_item operator[](int i) const;
  bool check_tasks() const;
  bool empty() const;
  const std::vector<todo_item> &get_list() const;
  const std::vector<todo_item> get_list_without_done() const;

 private:
  std::vector<todo_item> m_todos;
};

#endif
