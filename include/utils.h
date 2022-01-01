#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>
#include <string>

namespace utils {
const std::string HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";

const std::string TASX_FILE = HOME + "/.config/tasx/todos.json";

const std::string HELP =
    "Usage:\n tasx [<options>...]\n\n"
    "Options:\n"
    "--help, -h   Help menu\n"
    "none         Show stats\n"
    "list         Display list of tasks\n"
    "hidden       Display list with hidden done tasks\n"
    "done         Mark task done\n"
    "add          Create new task\n"
    "pr           Set priority [id] [priority{1-4}]\n"
    "do           Mark task in process\n"
    "edit         Edit task [id] [subject]\n"
    "delete       Remove task from list\n"
    "clear        Clear list\n\n"
    "Priority:\n"
    "1. Low - white color\n"
    "2. Medium - yellow color\n"
    "3. High - red color\n"
    "4. Critical - red bold color\n"
    "Status:\n\n"
    "1. Todo - [ ]\n"
    "2. In process - [*]\n"
    "3. Done - [x]\n";

}  // namespace utils

#endif
