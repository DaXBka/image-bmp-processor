#pragma once

#include "Filters//MatrixFilter.h"

class EdgeFilter : public MatrixFilter {
public:
    explicit EdgeFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;

private:
    void ProdMatrix(Image& image) override;
    long double threshold_;
};
