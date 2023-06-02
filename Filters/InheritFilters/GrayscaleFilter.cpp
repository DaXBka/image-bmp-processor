#include "GrayscaleFilter.h"

#include <stdexcept>

GrayscaleFilter::GrayscaleFilter(const std::vector<std::string>& args) : Filter(args) {
    if (!args_.empty()) {
        throw std::runtime_error(
            "(Error: GrayscaleFilter) Фильтр Grayscale принимает 0 аргументов. Было получено аргументов: " +
            std::to_string(args_.size()));
    }
}

void GrayscaleFilter::Make(Image& image) {
    for (size_t y = 0; y < image.height_; ++y) {
        for (size_t x = 0; x < image.width_; ++x) {
            Pixel& p = image[y][x];
            const double new_color = 0.299 * p.red + 0.587 * p.green + 0.114 * p.blue;

            p = {new_color, new_color, new_color};
        }
    }
}
