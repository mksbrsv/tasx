#ifndef UTILS_H
#define UTILS_H
#include <algorithm>
#include <cstdlib>
#include <string>

namespace utils {
const std::string HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";

const std::string TASX_FILE =
    HOME + "/.config/tasx/todos.json";  // TODO: change try to todos;

const std::string HELP =  // rewrite help page;
    "Usage:\n tasx [<options>...]\n\n"
    "Options:\n"
    "-help           Help menu\n"
    "none            Show stats\n"
    "-list           Display list of tasks\n"
    "-hidden         Display list with hidden done tasks. Note: option for "
    "-list\n"
    "-done           Mark task done: [@group_name] id\n"
    "-add [-group]    Create new task [@group_name], add new group "
    "[group_name]\n"
    "-pr             Set priority [@group_name] id priority{1-4}\n"
    "-do             Mark task in process [@group_name] id\n"
    "-edit           Edit task [@group_name] id subject\n"
    "-delete [-group] Remove task from list [@group_name] id, remove group "
    "[group_name]\n"
    "-clear          Clear list [@group_name]\n\n"
    "Addition:\n"
    "If no group name provided, program will use default group - 'Board'\n"
    "Priority:\n"
    "1. Low - white color\n"
    "2. Medium - yellow color\n"
    "3. High - red color\n"
    "4. Critical - red bold color\n"
    "Status:\n"
    "1. Todo - [ ]\n"
    "2. In process - [*]\n"
    "3. Done - [x]\n";

std::string to_lower(std::string str);
std::string to_upper(std::string str);

}  // namespace utils

#endif
