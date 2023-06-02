#include "PixelFilter.h"

#include <stdexcept>

PixelFilter::PixelFilter(const std::vector<std::string>& args) : Filter(args) {
    if (args_.size() != 1) {
        throw std::runtime_error("(Error: PixelFilter) Фильтр Pixel принимает 1 аргумент. Было получено аргументов: " +
                                 std::to_string(args_.size()));
    }

    size_ = std::stoi(args_[0]);
}

void PixelFilter::Make(Image& image) {
    for (int32_t y = 0; y < image.height_; y += size_) {
        for (int32_t x = 0; x < image.width_; x += size_) {
            double r = 0;
            double g = 0;
            double b = 0;

            for (int32_t k = 0; k < size_; ++k) {
                for (int32_t l = 0; l < size_; ++l) {
                    const Pixel& p = image.At(y + k, x + l);
                    r += p.red;
                    g += p.green;
                    b += p.blue;
                }
            }

            const double s2 = size_ * size_;
            for (int32_t k = 0; k < size_; ++k) {
                for (int32_t l = 0; l < size_; ++l) {
                    image.At(y + k, x + l) = {r / s2, g / s2, b / s2};
                }
            }
        }
    }
}
