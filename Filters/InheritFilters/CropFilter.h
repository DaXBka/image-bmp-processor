#pragma once

#include "Filters/Filter.h"

class CropFilter : public Filter {
public:
    explicit CropFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;

private:
    int32_t width_;
    int32_t height_;
};
