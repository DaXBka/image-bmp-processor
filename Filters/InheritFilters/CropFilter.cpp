#include "CropFilter.h"

#include <stdexcept>

CropFilter::CropFilter(const std::vector<std::string>& args) : Filter(args) {
    if (args_.size() != 2) {
        throw std::runtime_error("(Error: CropFilter) Фильтр Crop принимает 2 аргумента. Было получено аргументов: " +
                                 std::to_string(args_.size()));
    }

    width_ = std::stoi(args_[0]);
    height_ = std::stoi(args_[1]);
}

void CropFilter::Make(Image& image) {
    if (width_ >= 0 && width_ < image.width_) {
        for (size_t i = 0; i < image.height_; ++i) {
            image[i].resize(width_);
        }
        image.width_ = width_;
    }

    if (height_ >= 0 && height_ < image.height_) {
        for (size_t i = 0; i < image.height_ - height_; ++i) {
            image.GetMatrix().pop_front();
        }
        image.height_ = height_;
    }
}
