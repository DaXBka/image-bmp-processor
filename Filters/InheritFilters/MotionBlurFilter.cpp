#include "MotionBlurFilter.h"

#include <iostream>

MotionBlurFilter::MotionBlurFilter(const std::vector<std::string>& args) : MatrixFilter(args) {
    if (args_.size() != 1) {
        throw std::runtime_error(
            "(Error: MotionBlurFilter) Фильтр MotionBlur принимает 1 аргумент. Было получено аргументов: " +
            std::to_string(args_.size()));
    }
    int32_t size = std::stoi(args_[0]);
    double factor = std::stod(args_[0]);

    matrix_ = std::vector<std::vector<double>>(size, std::vector<double>(size, 0));

    for (size_t i = 0; i < size; ++i) {
        matrix_[i][i] = 1 / factor;
    }
}

void MotionBlurFilter::ProdMatrix(Image& image) {
    auto copy = image.GetMatrix();

    for (int32_t y = 0; y < image.height_; ++y) {
        for (int32_t x = 0; x < image.width_; ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;

            for (int32_t i = 0; i < matrix_.size(); ++i) {
                auto& matrix = matrix_[i][i];
                Pixel& p = image.At(y + i - 1, x + i - 1);

                red += matrix * p.red;
                green += matrix * p.green;
                blue += matrix * p.blue;
            }

            const double d_one = 1.0;
            Pixel& copy_p = copy[y][x];

            copy_p.red = std::min(d_one, std::max(0.0, red));
            copy_p.green = std::min(d_one, std::max(0.0, green));
            copy_p.blue = std::min(d_one, std::max(0.0, blue));
        }
    }

    image.SetMatrix(copy);
}

void MotionBlurFilter::Make(Image& image) {
    ProdMatrix(image);
}
