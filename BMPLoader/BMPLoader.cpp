#include "BMPLoader.h"

#include <fstream>
#include <cstring>

Image bmp_loader::Import(std::string &path) {
    std::ifstream file;

    file.open(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(
            "(Error: FileImport) Произошла ошибка при открытии файла. Возможно, указан неверный путь.");
    }

    const int header_size = 14;
    const int information_size = 40;
    const int pixel_bit = 24;

    unsigned char header[header_size];
    unsigned char information[information_size];

    file.read(reinterpret_cast<char *>(header), header_size);

    if (header[0] != 'B' || header[1] != 'M') {
        file.close();
        throw std::runtime_error("(Error: FileImport) Программа работает только с изображениями формата .bmp");
    }

    file.read(reinterpret_cast<char *>(information), information_size);

    const int pixel_bit_idx = 14;
    if (static_cast<int>(information[pixel_bit_idx]) != pixel_bit) {
        file.close();
        throw std::runtime_error(
            "(Error: FileImport) Программа работает только с глубиной цвета изображения, равной 24 бит");
    }

    const size_t image_width = information[4] + (information[5] << 8) + (information[6] << 16) + (information[7] << 24);
    const size_t image_height =
        information[8] + (information[9] << 8) + (information[10] << 16) + (information[11] << 24);
    const int32_t padding_cnt = (4 - (static_cast<int32_t>(image_width) * 3) % 4) % 4;

    Image image(image_width, image_height);

    std::memcpy(image.header_, header, header_size);
    std::memcpy(image.information_, information, information_size);

    for (size_t y = 0; y < image.height_; ++y) {
        for (size_t x = 0; x < image.width_; ++x) {
            unsigned char pixel[3];
            file.read(reinterpret_cast<char *>(pixel), 3);

            const auto red = static_cast<double>(pixel[2]) / 255.0;
            const auto green = static_cast<double>(pixel[1]) / 255.0;
            const auto blue = static_cast<double>(pixel[0]) / 255.0;

            image[y][x] = Pixel{red, green, blue};
        }

        file.ignore(padding_cnt);
    }

    file.close();

    return image;
}

void bmp_loader::Export(std::string &path, Image image) {
    std::ofstream file;

    file.open(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(
            "(Error: FileExport) Произошла ошибка при записи файла. Возможно, указан несуществующий путь");
    }

    unsigned char padding[3] = {0, 0, 0};
    const int32_t padding_cnt = (4 - (static_cast<int32_t>(image.width_) * 3) % 4) % 4;

    const int32_t header_size = 14;
    const int32_t information_size = 40;
    const int32_t file_size = static_cast<int32_t>(header_size + information_size + image.width_ * image.height_ * 3 +
                                                   padding_cnt * image.height_);

    const size_t header_it_end_cnt = 5;
    const size_t bit_cnt = 8;

    for (size_t i = 2; i <= header_it_end_cnt; ++i) {
        image.header_[i] = file_size >> bit_cnt * (i - 2);
    }

    const size_t info_it_width_start = 4;
    const size_t info_it_width_end = 7;

    const size_t info_it_height_start = 8;
    const size_t info_it_height_end = 11;

    for (size_t i = info_it_width_start; i <= info_it_width_end; ++i) {
        image.information_[i] = image.width_ >> bit_cnt * (i - info_it_width_start);
    }

    for (size_t i = info_it_height_start; i <= info_it_height_end; ++i) {
        image.information_[i] = image.height_ >> bit_cnt * (i - info_it_height_start);
    }

    file.write(reinterpret_cast<char *>(image.header_), header_size);
    file.write(reinterpret_cast<char *>(image.information_), information_size);

    for (size_t y = 0; y < image.height_; ++y) {
        for (size_t x = 0; x < image.width_; ++x) {
            Pixel &p = image[y][x];

            const unsigned char red = static_cast<char>(static_cast<uint8_t>(p.red * 255.0));
            const unsigned char green = static_cast<char>(static_cast<uint8_t>(p.green * 255.0));
            const unsigned char blue = static_cast<char>(static_cast<uint8_t>(p.blue * 255.0));

            unsigned char color[] = {blue, green, red};

            file.write(reinterpret_cast<char *>(color), 3);
        }

        file.write(reinterpret_cast<char *>(padding), padding_cnt);
    }

    file.close();
}
