#ifndef TODO_GROUP_H
#define TODO_GROUP_H

#include "todos.h"

struct group_type {
  group_type() = default;
  group_type(todo_list list, std::string name, int id)
      : list(list), name(name), id(id) {}
  todo_list list;
  std::string name;
  int id;
};

class todo_groups {
  using group_t = std::vector<group_type>;

 public:
  todo_groups() = default;
  void init(const std::string &file = utils::TASX_FILE);
  void close(const std::string &file = utils::TASX_FILE);
  group_type &operator[](int i);
  group_type operator[](int i) const;
  group_type &operator[](std::string &name);
  group_type operator[](std::string &name) const;
  int amount() const;
  int amount_tasks() const;
  int group_id(const std::string &name) const;
  void add_group(const std::string &group_name);
  void remove_group(const std::string &group_name);
  bool empty() const;

 private:
  bool is_empty(std::ifstream &file);

 private:
  group_t m_groups;
  std::string default_group = "Board";
};

#endif  // TODO_GROUP_H
