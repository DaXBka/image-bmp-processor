#include "MatrixFilter.h"

MatrixFilter::MatrixFilter(const std::vector<std::string>& args) : Filter(args) {
}

void MatrixFilter::ProdMatrix(Image& image) {
    auto copy = image.GetMatrix();

    for (int32_t y = 0; y < image.height_; ++y) {
        for (int32_t x = 0; x < image.width_; ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;

            for (int32_t i = 0; i < matrix_.size(); ++i) {
                for (int32_t j = 0; j < matrix_[i].size(); ++j) {
                    auto& matrix = matrix_[i][j];
                    Pixel& p = image.At(y + i - 1, x + j - 1);

                    red += matrix * p.red;
                    green += matrix * p.green;
                    blue += matrix * p.blue;
                }
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
