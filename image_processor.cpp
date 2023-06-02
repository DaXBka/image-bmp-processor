#include "BMPLoader/BMPLoader.h"
#include "Image/Image.h"
#include "Validator/Validator.h"
#include "Filters/InheritFilters/CropFilter.h"
#include "Filters/InheritFilters/GrayscaleFilter.h"
#include "Filters/InheritFilters/NegativeFilter.h"
#include "Filters/InheritFilters/SharpFilter.h"
#include "Filters/InheritFilters/EdgeFilter.h"
#include "Filters/InheritFilters/GaussianBlurFilter.h"
#include "Filters/InheritFilters/PixelFilter.h"
#include "Filters/InheritFilters/ThirdDimFilter.h"
#include "Filters/InheritFilters/MotionBlurFilter.h"
#include "Filters/InheritFilters/SmoothEdgeFilter.h"

#include <iostream>

namespace {
void PrintHelp() {
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << std::endl;
    std::cout << "\t\t\t *** Image Processor ***" << std::endl;
    std::cout << "Программа для применения фильтров на изображения формата BMP с глубиной 24 bit." << std::endl;
    std::cout << "Примеры работ в папке /work_examples." << std::endl;
    std::cout << std::endl;
    std::cout << "Использование:" << std::endl;
    std::cout << "   ./image_processor [input_filename].bmp [output_filename].bmp [FILTERS [ARGS]]" << std::endl;
    std::cout << std::endl;
    std::cout << "Доступные фильтры:" << std::endl;
    std::cout << "   -gs Чёрно-белый фильтр." << std::endl;
    std::cout << "   -neg Негативный фильтр." << std::endl;
    std::cout << "   -crop [width] [height] Обрезать изображения с левого верхнего края." << std::endl;
    std::cout << "   -sharp Повышение резкости изображения." << std::endl;
    std::cout << "   -edge [threshold] Обнаружение границ." << std::endl;
    std::cout << "   -blur [sigma] Размытие Гаусса." << std::endl;
    std::cout << "   -pixel [width] Пикселизация." << std::endl;
    std::cout << "   -motion [power] Размытие в движение." << std::endl;
    std::cout << "   -3d [distance] Эффект 3D." << std::endl;
    std::cout << "   -se Размытое обнаружение краёв с эффектом свечения." << std::endl;
    std::cout << std::endl;
    std::cout << "Пример запуска:" << std::endl;
    std::cout << "   ./image_processor home/lenna.bmp lenna_edge.bmp -edge 0.5 -gs" << std::endl;
    std::cout << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
}
}  // namespace

int main(int argc, char** argv) {
    if (argc < 3) {
        PrintHelp();
        return 1;
    }

    try {
        std::string input_path(argv[1]);
        std::string output_path(argv[2]);

        if (!validator::IsUnixPath(input_path)) {
            throw std::runtime_error(
                "(Error: InputPath) Указан неверный путь или неверный тип файла для импорта изображения.");
        }

        if (!validator::IsUnixPath(output_path)) {
            throw std::runtime_error(
                "(Error: OutputPath) Указан неверный путь или неверный тип файла для экспорта "
                "изображения.");
        }

        Image image = bmp_loader::Import(input_path);

        auto queue = validator::ParseTerminal(argc, argv);

        while (!queue.empty()) {
            auto& filter_name = queue.front().first;
            auto& args = queue.front().second;

            if (filter_name == "-crop") {
                CropFilter crop(args);
                crop.Make(image);
            } else if (filter_name == "-gs") {
                GrayscaleFilter gs(args);
                gs.Make(image);
            } else if (filter_name == "-neg") {
                NegativeFilter neg(args);
                neg.Make(image);
            } else if (filter_name == "-sharp") {
                SharpFilter sharp(args);
                sharp.Make(image);
            } else if (filter_name == "-edge") {
                EdgeFilter edge(args);
                edge.Make(image);
            } else if (filter_name == "-blur") {
                GaussianBlurFilter blur(args);
                blur.Make(image);
            } else if (filter_name == "-pixel") {
                PixelFilter pixel(args);
                pixel.Make(image);
            } else if (filter_name == "-3d") {
                ThirdDimFilter td(args);
                td.Make(image);
            } else if (filter_name == "-motion") {
                MotionBlurFilter motion(args);
                motion.Make(image);
            } else if (filter_name == "-se") {
                SmoothEdgeFilter se(args);
                se.Make(image);
            }

            queue.pop();
        }

        bmp_loader::Export(output_path, image);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
