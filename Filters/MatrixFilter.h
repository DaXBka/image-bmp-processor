#pragma once

#include "Filter.h"

class MatrixFilter : public Filter {
public:
    explicit MatrixFilter(const std::vector<std::string>& args);

protected:
    virtual void ProdMatrix(Image& image);

    std::vector<std::vector<double>> matrix_;
};
