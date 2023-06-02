#pragma once

#include "Filters/Filter.h"

class SmoothEdgeFilter : public Filter {
public:
    explicit SmoothEdgeFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;

private:
    std::vector<double> smooth_;
};
