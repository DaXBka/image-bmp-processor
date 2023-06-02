#pragma once

#include "Filters/Filter.h"

class GrayscaleFilter : public Filter {
public:
    explicit GrayscaleFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;
};
