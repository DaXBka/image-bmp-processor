#pragma once

#include <string>
#include <queue>
#include <vector>

using FilterArguments = std::pair<std::string, std::vector<std::string>>;

namespace validator {
static const std::vector<std::string> FILTERS = {"-gs",   "-crop",  "-neg", "-sharp",  "-edge",
                                                 "-blur", "-pixel", "-3d",  "-motion", "-se"};
bool IsUnixPath(const std::string &path);
bool IsParameter(const std::string &param);
bool IsFilter(const std::string &name);
std::queue<FilterArguments> ParseTerminal(int argc, char **argv);
std::queue<FilterArguments> ParseTerminal(int argc, std::vector<char *> &argv);
};  // namespace validator
