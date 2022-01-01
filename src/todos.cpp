#include "../include/todos.h"

#include <iterator>
#include <stdexcept>

void todo_list::save_list(const std::string &file) {
  using nlohmann::json;
  std::fstream out(file);
  if (!out.is_open()) {
    throw std::logic_error("Can't open file");
  }
  if (m_todos.empty()) return;
  json js;
  for (int i = 0; i < m_todos.size(); i++) {
    js[i]["todo"] = m_todos[i].get_subject();
    js[i]["status"] = static_cast<int>(m_todos[i].get_status());
    js[i]["id"] = m_todos[i].get_id();
    js[i]["priority"] = static_cast<int>(m_todos[i].get_priority());
  }
  out << std::setw(4) << js;
}

void todo_list::load_list(const std::string &file) {
  using nlohmann::json;
  std::fstream in(file);
  if (!in.is_open()) {
    throw std::logic_error("File doesn't exist. You should create it");
  }
  json js;
  in >> js;
  for (int i = 0; i < js.size(); i++) {
    todo_item ti(js[i]["todo"], js[i]["id"], js[i]["status"],
                 js[i]["priority"]);
    m_todos.push_back(ti);
  }
}

void todo_list::add_todo(const todo_item &todo) { m_todos.push_back(todo); }

void todo_list::add_todo(const std::string &subject) {
  m_todos.emplace_back(subject, m_todos[m_todos.size() - 1].get_id() + 1);
}

todo_item &todo_list::get_by_id(const int index) {
  for (auto it = m_todos.begin(); it != m_todos.end(); ++it) {
    if (it->get_id() == index) return *it;
  }
}

void todo_list::edit_todo(const int index, const std::string &subject) {
  get_by_id(index).set_subject(subject);
}

void todo_list::remove_todo(const int index) {
  if (index == m_todos.size() - 1) {
    m_todos.pop_back();
    return;
  }
  m_todos.erase(m_todos.begin() + index);
}

void todo_list::set_priority(const int index, priority pr) {
  get_by_id(index).set_priority(pr);
}

void todo_list::set_status(const int index, status st) {
  get_by_id(index).set_status(st);
}

void todo_list::clear() { m_todos.clear(); }

bool todo_list::is_no_tasks_todo() const {
  auto it = std::find_if(
      m_todos.begin(), m_todos.end(),
      [](const todo_item &t) { return t.get_status() != status::done; });
  return it == m_todos.end();
}

const std::vector<todo_item> &todo_list::get_list() const { return m_todos; }
const std::vector<todo_item> todo_list::get_list_without_done() const {
  std::vector<todo_item> list_without_done;
  std::copy_if(
      m_todos.begin(), m_todos.end(), std::back_inserter(list_without_done),
      [](const todo_item &ti) { return ti.get_status() != status::done; });
  return list_without_done;
}
