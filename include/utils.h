#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>
#include <string>

namespace utils {
const std::string HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";

const std::string TASX_FILE =
    HOME + "/code/cpp/tasx/todo.json";  // TODO: change folder to config folder

const std::string HELP =
    "Usage:\n tasx [<options>...]\n\n"
    "Options:\n"
    "none           Show stats\n"
    "--help, -h     Help menu\n"
    "--list, -l     Display list of tasks\n"
    "--done, -d     Mark task done\n"
    "--new, -n      Create new task\n"
    "--priority, -n Set priority [id] [priority{1-4}]\n"
    "--remove, -r   Remove task from list\n"
    "--clear, -c    Clear list\n\n"
    "Priority:\n"
    "1. Low - white color\n"
    "2. Medium - yellow color\n"
    "3. High - red color\n"
    "4. Critical - red bold color\n";

}  // namespace utils

#endif
