#ifndef UTILS_H
#define UTILS_H
#include <cstdlib>
#include <string>

namespace utils {
const std::string HOME = std::getenv("HOME") ? std::getenv("HOME") : ".";

const std::string config_folder =
    HOME + "/code/cpp/tasx/todo.json";  // TODO: change folder to config folder

}  // namespace utils

#endif
