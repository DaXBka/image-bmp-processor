#include "Image.h"

Image::Image(size_t width, size_t height) : width_(width), height_(height) {
    matrix_ = Matrix(height, std::vector<Pixel>(width));
}

std::vector<Pixel>& Image::operator[](size_t y) {
    return matrix_[y];
}

const std::vector<Pixel>& Image::operator[](size_t y) const {
    return matrix_[y];
}

Pixel& Image::At(int32_t i, int32_t j) {
    int32_t y = i;
    int32_t x = j;

    if (y < 0) {
        y = 0;
    } else if (y >= height_) {
        y = static_cast<int32_t>(height_) - 1;
    }

    if (x < 0) {
        x = 0;
    } else if (x >= width_) {
        x = static_cast<int32_t>(width_) - 1;
    }

    return this->operator[](y)[x];
}

Matrix& Image::GetMatrix() {
    return matrix_;
}

void Image::SetMatrix(Matrix& other_matrix) {
    matrix_ = other_matrix;
}