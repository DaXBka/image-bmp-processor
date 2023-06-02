#include "SharpFilter.h"

#include <stdexcept>

SharpFilter::SharpFilter(const std::vector<std::string>& args) : MatrixFilter(args) {
    if (!args_.empty()) {
        throw std::runtime_error(
            "(Error: SharpFilter) Фильтр Sharpening принимает 0 аргументов. Было получено аргументов: " +
            std::to_string(args_.size()));
    }
    const double five = 5;
    matrix_ = {{0, -1, 0}, {-1, five, -1}, {0, -1, 0}};
}

void SharpFilter::Make(Image& image) {
    ProdMatrix(image);
}
