#include "../include/todo.h"

todo_item::todo_item(const std::string &subject, int id, status st, priority pr)
    : m_subject(subject), m_id(id), m_status(st), m_priority(pr) {}

status todo_item::get_status() const { return m_status; }

void todo_item::set_status(status st) { m_status = st; }

std::string todo_item::get_subject() const { return m_subject; }

void todo_item::set_subject(const std::string &subject) { m_subject = subject; }

int todo_item::get_id() const { return m_id; }

priority todo_item::get_priority() const { return m_priority; }

void todo_item::set_priority(priority pr) { m_priority = pr; }

const std::string todo_item::str_status() const {
  switch (m_status) {
    case status::todo: {
      return "[ ]";
    }
    case status::in_process: {
      return "[*]";
    }
    case status::done: {
      return "[x]";
    }
  }
}

std::string todo_item::to_string() const {
  std::string status = str_status();
  std::string result = status + " " + m_subject;
  return result;
}

std::ofstream &operator<<(std::ofstream &out, const todo_item &todo) {
  std::string status = todo.str_status();
  out << status << todo.m_subject << "\n";
  out << status << todo.m_subject << "\n";
  return out;
}
