#include "ThirdDimFilter.h"

#include <stdexcept>

ThirdDimFilter::ThirdDimFilter(const std::vector<std::string>& args) : Filter(args) {
    if (args_.size() != 1) {
        throw std::runtime_error("(Error: ThirdDimFilter) Фильтр 3D принимает 1 аргумент. Было получено аргументов: " +
                                 std::to_string(args_.size()));
    }

    distance_ = std::stoi(args_[0]);
}

void ThirdDimFilter::Make(Image& image) {
    Image red = Image(image.width_, image.height_);
    Image blue = Image(image.width_, image.height_);

    for (size_t y = 0; y < image.height_; ++y) {
        for (size_t x = 0; x < image.width_; ++x) {
            const Pixel& p = image[y][x];

            red[y][x] = {p.red, p.green / 2, 0};
            blue[y][x] = {0, p.green / 2, p.blue};
        }
    }

    for (int32_t y = 0; y < image.height_; ++y) {
        for (int32_t x = 0; x < image.width_; ++x) {
            const Pixel& r = red.At(y, x - distance_);
            const Pixel& b = blue.At(y, x + distance_);

            image[y][x] = {r.red + b.red, r.green + b.green, r.blue + b.blue};
        }
    }
}
