#include "../include/todos.h"

#include <iterator>

void todo_list::save_list(const std::string &file) {
  // std::fstream out(file);
  // if (out.is_open())
  //     std::copy(m_todos.begin(), m_todos.end(),
  //     std::ostream_iterator<todo_list>(out, "\n"));
  // else {}
  // // add log
}

void todo_list::load_list(const std::string &file) {
  using nlohmann::json;
  std::fstream in(file);
  json j;
  try {
    in >> j;

  } catch (std::exception &ex) {
    std::cout << ex.what();
  }
  for (int i = 0; i < j.size(); i++) {
    todo_item ti(j[i]["todo"], j[i]["id"], j[i]["status"]);
    m_todos.push_back(ti);
  }
}

void todo_list::add_todo(const todo_item &todo) { m_todos.push_back(todo); }

void todo_list::add_todo(const std::string &subject) {
  m_todos.emplace_back(subject, m_todos[m_todos.size() - 1].get_id() + 1);
}

void todo_list::done(const int index) {
  for (int i = 0; i < m_todos.size(); i++) {
    if (index == i) {
      m_todos[i].set_status(true);
    }
  }
}

const std::vector<todo_item> todo_list::get_list() const { return m_todos; }
