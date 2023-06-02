#include "EdgeFilter.h"
#include "GrayscaleFilter.h"

#include <stdexcept>

EdgeFilter::EdgeFilter(const std::vector<std::string>& args) : MatrixFilter(args) {
    if (args_.size() != 1) {
        throw std::runtime_error("(Error: EdgeFilter) Фильтр Edge принимает 1 аргумент. Было получено аргументов: " +
                                 std::to_string(args_.size()));
    }

    threshold_ = std::stold(args_[0]);
    matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
}

void EdgeFilter::Make(Image& image) {
    std::vector<std::string> gs_args = {};
    GrayscaleFilter gs(gs_args);

    gs.Make(image);
    ProdMatrix(image);
}

void EdgeFilter::ProdMatrix(Image& image) {
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

            const double ld_one = 1.0;
            const double ld_zero = 0.0;

            const bool is_red_more_ts = red > threshold_;
            const bool is_green_more_ts = green > threshold_;
            const bool is_blue_more_ts = blue > threshold_;

            Pixel& copy_p = copy[y][x];

            if (is_red_more_ts || is_green_more_ts || is_blue_more_ts) {
                copy_p = {ld_one, ld_one, ld_one};
            } else {
                copy_p = {ld_zero, ld_zero, ld_zero};
            }
        }
    }

    image.SetMatrix(copy);
}
