#include "../include/todos.h"

#include <iterator>
#include <stdexcept>

todo_list::todo_list() noexcept { m_todos.reserve(10); }

void todo_list::save_list(nlohmann::json &j, const std::string &file) {
  for (int i = 0; i < m_todos.size(); i++) {
    j[i]["todo"] = m_todos[i].get_subject();
    j[i]["status"] = static_cast<int>(m_todos[i].get_status());
    j[i]["id"] = m_todos[i].get_id();
    j[i]["priority"] = static_cast<int>(m_todos[i].get_priority());
  }
}

void todo_list::load_list(nlohmann::json &j, const std::string &file) {
  for (int i = 0; i < j.size(); i++) {
    todo_item ti(j[i]["todo"], j[i]["id"], j[i]["status"], j[i]["priority"]);
    m_todos.push_back(ti);
  };
}

std::pair<error_code, std::string> todo_list::add_todo(const todo_item &todo) {
  error_code ec = error_code::success;
  std::string msg;
  try {
    m_todos.push_back(todo);
  } catch (std::exception &ex) {
    msg = ex.what();
    ec = error_code::fail;
  }
  return {ec, msg};
}

std::pair<error_code, std::string> todo_list::add_todo(
    const std::string &subject) {
  int id;
  std::string msg;
  error_code ec = error_code::success;
  if (m_todos.empty())
    id = 0;
  else
    id = m_todos[m_todos.size() - 1].get_id() + 1;
  try {
    m_todos.emplace_back(subject, id);
  } catch (std::exception &ex) {
    msg = ex.what();
    ec = error_code::fail;
  }
  return {ec, msg};
}

todo_item &todo_list::operator[](int i) { return m_todos[i]; }

todo_item todo_list::operator[](int i) const { return m_todos[i]; }

std::pair<error_code, std::string> todo_list::edit_todo(
    const int index, const std::string &subject) {
  error_code ec = error_code::success;
  std::string msg = "";
  try {
    m_todos[index].set_subject(subject);
  } catch (std::exception &ex) {
    ec = error_code::fail;
    msg = ex.what();
  }
  return {ec, msg};
}

std::pair<error_code, std::string> todo_list::remove_todo(const int index) {
  error_code ec = error_code::success;
  std::string msg = "";
  try {
    if (index == m_todos.size() - 1) {
      m_todos.pop_back();
    } else {
      m_todos.erase(m_todos.begin() + index);
    }
  } catch (std::exception &ex) {
    ec = error_code::fail;
    msg = ex.what();
  }
  return {ec, msg};
}

std::pair<error_code, std::string> todo_list::set_priority(const int index,
                                                           priority pr) {
  error_code ec = error_code::success;
  std::string msg = "";
  try {
    m_todos[index].set_priority(pr);
  } catch (std::exception &ex) {
    ec = error_code::fail;
    msg = ex.what();
  }
  return {ec, msg};
}

std::pair<error_code, std::string> todo_list::set_status(const int index,
                                                         status st) {
  error_code ec = error_code::success;
  std::string msg = "";
  try {
    m_todos[index].set_status(st);
  } catch (std::exception &ex) {
    ec = error_code::fail;
    msg = ex.what();
  }
  return {ec, msg};
}

void todo_list::clear() { m_todos.clear(); }

int todo_list::amount() const { return m_todos.size(); }

bool todo_list::check_tasks() const {
  auto it = std::find_if(
      m_todos.begin(), m_todos.end(),
      [](const todo_item &t) { return t.get_status() != status::done; });
  return it == m_todos.end();
}

bool todo_list::empty() const { return m_todos.empty(); }

const std::vector<todo_item> &todo_list::get_list() const { return m_todos; }
const std::vector<todo_item> todo_list::get_list_without_done() const {
  std::vector<todo_item> list_without_done;
  std::copy_if(
      m_todos.begin(), m_todos.end(), std::back_inserter(list_without_done),
      [](const todo_item &ti) { return ti.get_status() != status::done; });
  return list_without_done;
}
