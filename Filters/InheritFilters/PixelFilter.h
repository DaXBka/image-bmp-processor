#pragma once

#include "Filters/Filter.h"

class PixelFilter : public Filter {
public:
    explicit PixelFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;

private:
    int32_t size_;
};
