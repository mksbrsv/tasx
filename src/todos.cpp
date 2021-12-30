#include "../include/todos.h"

#include <iterator>

void todo_list::save_list(const std::string &file) {
  using nlohmann::json;
  json js;
  for (int i = 0; i < m_todos.size(); i++) {
    js[i]["todo"] = m_todos[i].get_subject();
    js[i]["status"] = m_todos[i].get_status();
    js[i]["id"] = m_todos[i].get_id();
  }
  std::fstream out(file);
  out << js;
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

void todo_list::remove_todo(const int index) {
  if (index == m_todos.size() - 1) {
    m_todos.pop_back();
    return;
  }
  m_todos.erase(m_todos.begin() + index);
}

void todo_list::done(const int index) {
  for (int i = 0; i < m_todos.size(); i++) {
    if (index == i) {
      m_todos[i].set_status(true);
    }
  }
}

void todo_list::clear() { m_todos.clear(); }

const std::vector<todo_item> todo_list::get_list() const { return m_todos; }
