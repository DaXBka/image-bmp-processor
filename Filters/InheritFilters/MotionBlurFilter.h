#pragma once

#include "Filters/MatrixFilter.h"

class MotionBlurFilter : public MatrixFilter {
public:
    explicit MotionBlurFilter(const std::vector<std::string>& args);
    void ProdMatrix(Image& image) override;
    void Make(Image& image) override;
};
