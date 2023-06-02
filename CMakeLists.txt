cmake_minimum_required(VERSION 3.0)

project(ImageProcessor)

include_directories(.)

add_executable(
        image_processor
        image_processor.cpp
        BMPLoader/BMPLoader.cpp
        Image/Image.cpp
        Filters/Filter.cpp
        Validator/Validator.cpp
        Filters/InheritFilters/CropFilter.cpp
        Filters/InheritFilters/GrayscaleFilter.cpp
        Filters/InheritFilters/NegativeFilter.cpp
        Filters/InheritFilters/GaussianBlurFilter.cpp
        Filters/InheritFilters/SharpFilter.cpp
        Filters/InheritFilters/EdgeFilter.cpp
        Filters/MatrixFilter.cpp
        Filters/InheritFilters/PixelFilter.cpp
        Filters/InheritFilters/ThirdDimFilter.cpp
        Filters/InheritFilters/MotionBlurFilter.cpp
        Filters/InheritFilters/SmoothEdgeFilter.cpp
)

add_catch(
        test_image_processor
        test.cpp
        BMPLoader/BMPLoader.cpp
        Image/Image.cpp
        Filters/Filter.cpp
        Validator/Validator.cpp
        Filters/InheritFilters/CropFilter.cpp
        Filters/InheritFilters/GrayscaleFilter.cpp
        Filters/InheritFilters/NegativeFilter.cpp
        Filters/InheritFilters/GaussianBlurFilter.cpp
        Filters/InheritFilters/SharpFilter.cpp
        Filters/InheritFilters/EdgeFilter.cpp
        Filters/MatrixFilter.cpp
        Filters/InheritFilters/PixelFilter.cpp
        Filters/InheritFilters/ThirdDimFilter.cpp
        Filters/InheritFilters/MotionBlurFilter.cpp
        Filters/InheritFilters/SmoothEdgeFilter.cpp
)
