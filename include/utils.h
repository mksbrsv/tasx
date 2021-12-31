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
    "none           Show stats\n"
    "--help, -h     Help menu\n"
    "--list, -l     Display list of tasks\n"
    "--done, -d     Mark task done\n"
    "--new, -n      Create new task\n"
    "--priority, -p Set priority [id] [priority{1-4}]\n"
    "--go, -g       Mark task in process\n"
    "--remove, -r   Remove task from list\n"
    "--clear, -c    Clear list\n\n"
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
