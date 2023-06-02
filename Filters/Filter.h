#pragma once

#include <string>
#include <vector>

#include "Image/Image.h"

class Filter {
public:
    explicit Filter(const std::vector<std::string>& args);
    virtual ~Filter() = default;
    virtual void Make(Image& image) = 0;

protected:
    std::vector<std::string> args_;
};
