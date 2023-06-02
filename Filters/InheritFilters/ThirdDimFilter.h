#pragma once

#include "Filters/Filter.h"

class ThirdDimFilter : public Filter {
public:
    explicit ThirdDimFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;

private:
    int32_t distance_;
};
