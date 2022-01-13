#include "../include/group.h"

#include <fmt/color.h>

group_type& todo_groups::operator[](int i) { return m_groups[i]; }

group_type todo_groups::operator[](int i) const { return m_groups[i]; }

group_type& todo_groups::operator[](std::string& name) {
  auto it = std::find_if(
      m_groups.begin(), m_groups.end(), [&name](const group_type& group) {
        return utils::to_lower(group.name) == utils::to_lower(name);
      });
  if (it == m_groups.end())
    throw std::logic_error("Can't find a group with name you provided");
  return *it;
}
group_type todo_groups::operator[](std::string& name) const {
  auto it = std::find_if(
      m_groups.begin(), m_groups.end(), [&name](const group_type& group) {
        return utils::to_lower(group.name) == utils::to_lower(name);
      });
  if (it == m_groups.end())
    throw std::logic_error("Can't find a group with name you provided");
  return *it;
}

int todo_groups::amount() const { return m_groups.size(); }

int todo_groups::amount_tasks() const {
  int amount = 0;
  for (auto& gr : m_groups) {
    amount += gr.list.amount();
  }
  return amount;
}

void todo_groups::add_group(const std::string& group_name) {
  todo_list empty_list;
  int id;
  if (m_groups.empty())
    id = 0;
  else
    id = m_groups[m_groups.size() - 1].id + 1;
  m_groups.push_back(group_type(empty_list, group_name, id));
}

void todo_groups::remove_group(const std::string& group_name) {
  if (group_name == m_groups[m_groups.size() - 1].name) {
    m_groups.pop_back();
  } else {
    auto it = std::find_if(m_groups.begin(), m_groups.end(),
                           [&group_name](const group_type& group) {
                             return utils::to_lower(group.name) ==
                                    utils::to_lower(group_name);
                           });
    m_groups.erase(it);
  }
}

bool todo_groups::empty() const {
  int empty_groups = 0;
  std::for_each(m_groups.begin(), m_groups.end(), [&empty_groups](auto group) {
    if (group.list.empty()) empty_groups++;
  });
  return empty_groups == amount();
}

bool todo_groups::is_empty(std::ifstream& file) {
  // return file.peek() == std::ifstream::traits_type::eof();
  return file.peek() == EOF;
}

void todo_groups::init(
    const std::string& file) {  // TODO: add check for empty file
  using nlohmann::json;
  std::ifstream in;
  in.open(file);
  if (is_empty(in)) {
    add_group(default_group);
    return;
  }
  json js;
  json js_list;
  in >> js;
  for (int i = 0; i < js.size(); i++) {
    group_type group;
    group.id = js[i]["id"];
    group.name = js[i]["name"];
    js_list = js[i]["list"];
    if (js_list.is_null()) {
      group.list = todo_list();
    } else {
      group.list.load_list(js_list);
    }
    m_groups.push_back(group);
  }
}

void todo_groups::close(const std::string& file) {
  using nlohmann::json;
  std::fstream out;
  out.open(file, std::ios_base::out);
  json js;
  json js_list;
  for (int i = 0; i < m_groups.size(); i++) {
    js[i]["id"] = m_groups[i].id;
    js[i]["name"] = m_groups[i].name;
    m_groups[i].list.save_list(js_list);
    js[i]["list"] = js_list;
    js_list = json();
  }
  out << std::setw(4) << js;
}
