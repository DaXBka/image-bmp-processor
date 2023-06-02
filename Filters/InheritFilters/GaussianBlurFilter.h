#pragma once

#include "Filters//Filter.h"

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;

private:
    std::vector<double> kernel_;
    int32_t kernel_size_;
};
