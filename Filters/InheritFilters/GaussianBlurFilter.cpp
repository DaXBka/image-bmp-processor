#include "GaussianBlurFilter.h"

#include <cmath>
#include <stdexcept>

GaussianBlurFilter::GaussianBlurFilter(const std::vector<std::string>& args) : Filter(args) {
    if (args_.size() != 1) {
        throw std::runtime_error(
            "(Error: GaussianBlurFilter) Фильтр GaussianBlur принимает 1 аргумент. Получено аргументов: " +
            std::to_string(args_.size()));
    }

    const double sigma = std::stod(args_[0]);
    const double sigma_coef = 3;

    kernel_size_ = static_cast<int32_t>(std::ceil(sigma * sigma_coef * 2));
    kernel_ = std::vector<double>(kernel_size_);

    const double half_kernel_size = std::ceil(sigma * sigma_coef);
    const double s2 = 2 * sigma * sigma;
    double sum = 0;

    for (int32_t i = 0; i < kernel_size_; ++i) {
        kernel_[i] = exp((-(i - half_kernel_size) * (i - half_kernel_size)) / s2);
        sum += kernel_[i];
    }

    for (size_t i = 0; i < kernel_size_; ++i) {
        kernel_[i] /= sum;
    }
}

void GaussianBlurFilter::Make(Image& image) {
    Image tmp(image.width_, image.height_);
    int32_t half_ker_size = kernel_size_ / 2;

    for (int32_t y = 0; y < image.height_; ++y) {
        for (int32_t x = 0; x < image.width_; ++x) {
            double red_sum = 0;
            double green_sum = 0;
            double blue_sum = 0;

            for (int32_t k = 0; k < kernel_size_; ++k) {
                int32_t xl = x + k - half_ker_size;

                Pixel& p = image.At(y, xl);
                auto& ker_elem = kernel_[k];

                red_sum += p.red * ker_elem;
                green_sum += p.green * ker_elem;
                blue_sum += p.blue * ker_elem;
            }

            tmp[y][x] = {red_sum, green_sum, blue_sum};
        }
    }

    for (int32_t x = 0; x < image.width_; ++x) {
        for (int32_t y = 0; y < image.height_; ++y) {
            double red_sum = 0;
            double green_sum = 0;
            double blue_sum = 0;

            for (int32_t k = 0; k < kernel_size_; ++k) {
                int32_t yl = y + k - half_ker_size;

                Pixel& p = tmp.At(yl, x);
                auto& ker_elem = kernel_[k];

                red_sum += p.red * ker_elem;
                green_sum += p.green * ker_elem;
                blue_sum += p.blue * ker_elem;
            }
            image[y][x] = {red_sum, green_sum, blue_sum};
        }
    }
}