#pragma once

#include <string>

#include "Image/Image.h"

namespace bmp_loader {
Image Import(std::string& path);
void Export(std::string& path, Image image);
};  // namespace bmp_loader
