#include "SmoothEdgeFilter.h"
#include "EdgeFilter.h"

#include <cmath>
#include <stdexcept>

SmoothEdgeFilter::SmoothEdgeFilter(const std::vector<std::string>& args) : Filter(args) {
    if (!args_.empty()) {
        throw std::runtime_error(
            "(Error: SmoothEdgeFilter) Фильтр SmoothEdge принимает 0 аргументов. Получено аргументов: " +
            std::to_string(args_.size()));
    }

    const int32_t s_size = 30;
    const int32_t half_s_size = s_size / 2;

    const double coef = -50;
    double sum = 0;

    smooth_ = std::vector<double>(s_size);
    for (int32_t i = 0; i < smooth_.size(); ++i) {
        smooth_[i] = exp((std::pow(i - half_s_size, 2)) / coef);
        sum += smooth_[i];
    }

    std::for_each(smooth_.begin(), smooth_.end(), [sum](double& v) { v /= sum; });
}

void SmoothEdgeFilter::Make(Image& image) {
    std::vector<std::string> edge_args = {"0.1"};
    EdgeFilter edge(edge_args);
    edge.Make(image);

    const int32_t s_size = static_cast<int32_t>(smooth_.size());
    const int32_t half_s = s_size / 2;

    for (int32_t y = 0; y < image.height_; ++y) {
        for (int32_t x = 0; x < image.width_; ++x) {
            double r_x = 0;
            double g_x = 0;
            double b_x = 0;

            double r_y = 0;
            double g_y = 0;
            double b_y = 0;

            for (int32_t l = 0; l < s_size; ++l) {
                auto& coef = smooth_[l];

                Pixel& p_x = image.At(y, x + l - half_s);
                r_x += p_x.red * coef;
                g_x += p_x.green * coef;
                b_x += p_x.blue * coef;

                Pixel& p_y = image.At(y + l - half_s, x);
                r_y += p_y.red * coef;
                g_y += p_y.green * coef;
                b_y += p_y.blue * coef;
            }

            Pixel& p = image[y][x];

            p.red = std::min(1.0, std::max(0.0, r_x + r_y));
            p.green = std::min(1.0, std::max(0.0, g_x + g_y));
            p.blue = std::min(1.0, std::max(0.0, b_x + b_y));
        }
    }
}
