#include "Validator.h"

#include <regex>

bool validator::IsUnixPath(const std::string& path) {
    if (path.empty()) {
        return false;
    }

    const std::regex path_regex("^((.)|(..))?/?(([^/\n]|(((.)|(..))))+/)*[^./\n ]+(.bmp)$");
    return std::regex_match(path, path_regex);
}

bool validator::IsParameter(const std::string& param) {
    if (param.empty()) {
        return false;
    }

    for (size_t i = 0; i < param.size(); ++i) {
        if (!std::isdigit(param[i])) {
            if (param[i] == '.' && std::count(param.begin(), param.end(), '.') == 1) {
                continue;
            }

            return false;
        }
    }

    return true;
}

bool validator::IsFilter(const std::string& name) {
    if (name.empty()) {
        return false;
    }

    if (name[0] != '-') {
        return false;
    }

    return std::find(FILTERS.begin(), FILTERS.end(), name) != FILTERS.end();
}

std::queue<FilterArguments> validator::ParseTerminal(int argc, char** argv) {
    std::queue<FilterArguments> queue;

    for (size_t i = 3; i < argc; ++i) {
        if (IsFilter(argv[i])) {
            std::string filter_name(argv[i]);
            std::vector<std::string> args;

            while (i + 1 < argc && IsParameter(argv[i + 1])) {
                args.push_back(argv[i + 1]);
                ++i;
            }

            queue.push({filter_name, args});
        } else {
            throw std::runtime_error(
                "(Error: SelectFilter) Задан неверный аргумент или несуществующий фильтр. Воспользуйтесь памяткой, "
                "запустив программу без аргументов");
        }
    }

    return queue;
}

std::queue<FilterArguments> validator::ParseTerminal(int argc, std::vector<char*>& argv) {
    std::queue<FilterArguments> queue;

    for (size_t i = 3; i < argc; ++i) {
        if (IsFilter(argv[i])) {
            std::string filter_name(argv[i]);
            std::vector<std::string> args;

            while (i + 1 < argc && IsParameter(argv[i + 1])) {
                args.push_back(argv[i + 1]);
                ++i;
            }

            queue.push({filter_name, args});
        } else {
            throw std::runtime_error(
                "(Error: SelectFilter) Задан неверный аргумент или несуществующий фильтр. Воспользуйтесь памяткой, "
                "запустив программу без аргументов");
        }
    }

    return queue;
}