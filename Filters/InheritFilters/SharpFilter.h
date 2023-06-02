#pragma once

#include "Filters/MatrixFilter.h"

class SharpFilter : public MatrixFilter {
public:
    explicit SharpFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;
};
