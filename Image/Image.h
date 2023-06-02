#pragma once

#include "Pixel/Pixel.h"

#include <cstddef>
#include <deque>
#include <vector>

namespace {
constexpr int32_t HeaderSize = 14;
constexpr int32_t InformationSize = 40;
}  // namespace

using Matrix = std::deque<std::vector<Pixel>>;

class Image {
    Matrix matrix_;

public:
    Image(size_t width, size_t height);

    std::vector<Pixel>& operator[](size_t y);
    const std::vector<Pixel>& operator[](size_t y) const;
    Pixel& At(int32_t i, int32_t j);

    Matrix& GetMatrix();
    void SetMatrix(Matrix& other);

    size_t width_;
    size_t height_;

    unsigned char header_[HeaderSize];
    unsigned char information_[InformationSize];
};
