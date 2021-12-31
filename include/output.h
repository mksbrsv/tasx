#ifndef OUTPUT_H
#define OUTPUT_H
#include <fmt/color.h>

#include <tuple>

#include "todos.h"

/*
Priorities:
1 - low
2 - medium
3 - high
4 - critical
*/

namespace output {
void choose_priority(const todo_item& item, std::string& formatted_string);

std::string low_priority(const todo_item& item);
void med_priority(const todo_item& item, std::string& formatted_string);
void high_priority(const todo_item& item, std::string& formatted_string);
void critical_priority(const todo_item& item, std::string& formatted_string);
void done_todo(const todo_item& item, std::string& formatted_string);

std::tuple<int, int, int, int> calc_stats(const todo_list& list);
std::string stats(const todo_list& list);

void colors();
}  // namespace output

#endif  // OUTPUT_H
