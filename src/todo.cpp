#include "../include/todo.h"

todo_item::todo_item(const std::string &subject, int id, bool status)
    : m_subject(subject), m_id(id), m_status(status) {}

bool todo_item::get_status() const { return m_status; }

void todo_item::set_status(bool status) { m_status = status; }

std::string todo_item::get_subject() const { return m_subject; }

int todo_item::get_id() const { return m_id; }

const std::string todo_item::str_status() const {
  return m_status ? "[x]" : "[ ]";
}

std::string todo_item::to_string() const {
  std::string status = m_status ? "[x]" : "[ ]";
  std::string result = status + " " + m_subject;
  return result;
}

std::ofstream &operator<<(std::ofstream &out, const todo_item &todo) {
  if (todo.m_status) {
    out << "[x]" << todo.m_subject << "\n";
  } else {
    out << "[ ]" << todo.m_subject << "\n";
  }
  return out;
}
