#include "NegativeFilter.h"

#include <stdexcept>

NegativeFilter::NegativeFilter(const std::vector<std::string>& args) : Filter(args) {
    if (!args_.empty()) {
        throw std::runtime_error(
            "(Error: NegativeFilter) Фильтр Negative принимает 0 аргументов. Было получено аргументов: " +
            std::to_string(args_.size()));
    }
}

void NegativeFilter::Make(Image& image) {
    for (size_t y = 0; y < image.height_; ++y) {
        for (size_t x = 0; x < image.width_; ++x) {
            Pixel& p = image[y][x];

            p = {1 - p.red, 1 - p.green, 1 - p.blue};
        }
    }
}
