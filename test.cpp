#include <catch.hpp>

#include "Validator/Validator.h"
#include "Image/Image.h"
#include "Filters/InheritFilters/GrayscaleFilter.h"
#include "Filters/InheritFilters/NegativeFilter.h"
#include "Filters/InheritFilters/SharpFilter.h"
#include "Filters/InheritFilters/ThirdDimFilter.h"

using FilterArguments = std::pair<std::string, std::vector<std::string>>;
using Matrix = std::deque<std::vector<Pixel>>;

static void RequireMatrices(const Matrix& image, const Matrix& valid) {
    const double eps = 1e-6;

    if (image.size() != valid.size()) {
        FAIL("image.height != valid.height");
    }

    if (!image.empty() && image[0].size() != valid[0].size()) {
        FAIL("image.width != valid.width");
    }

    for (size_t i = 0; i < image.size(); ++i) {
        for (size_t j = 0; j < image[i].size(); ++j) {
            bool red = image[i][j].red - valid[i][j].red < eps;
            bool green = image[i][j].green - valid[i][j].green < eps;
            bool blue = image[i][j].blue - valid[i][j].blue < eps;

            REQUIRE((red && green && blue));
        }
    }
}

TEST_CASE("TEST VALIDATOR::IS_PARAMETER") {
    REQUIRE(validator::IsParameter("8"));
    REQUIRE(validator::IsParameter("12"));
    REQUIRE(validator::IsParameter("3.5"));
    REQUIRE(validator::IsParameter("0.1"));

    REQUIRE(!validator::IsParameter("3,5"));
    REQUIRE(!validator::IsParameter("qwerty"));
    REQUIRE(!validator::IsParameter("2c"));
    REQUIRE(!validator::IsParameter(""));
    REQUIRE(!validator::IsParameter("-gs"));
    REQUIRE(!validator::IsParameter("-blur"));
}

TEST_CASE("TEST VALIDATOR::IS_FILTER") {
    REQUIRE(validator::IsFilter("-gs"));
    REQUIRE(validator::IsFilter("-blur"));
    REQUIRE(validator::IsFilter("-neg"));
    REQUIRE(validator::IsFilter("-pixel"));

    REQUIRE(!validator::IsFilter("321"));
    REQUIRE(!validator::IsFilter("5.5"));
    REQUIRE(!validator::IsFilter("abacaba"));
    REQUIRE(!validator::IsFilter("_blur"));
    REQUIRE(!validator::IsFilter("-blur 10"));
    REQUIRE(!validator::IsFilter("-filter"));
    REQUIRE(!validator::IsFilter("-coffe"));
    REQUIRE(!validator::IsFilter("-"));
    REQUIRE(!validator::IsFilter(" "));
    REQUIRE(!validator::IsFilter(""));
}

TEST_CASE("TEST VALIDATOR::IS_UNIX_PATH") {
    REQUIRE(validator::IsUnixPath("input.bmp"));
    REQUIRE(validator::IsUnixPath("/output.bmp"));
    REQUIRE(validator::IsUnixPath("some-dir/lenna.bmp"));
    REQUIRE(validator::IsUnixPath("./home/lenna.bmp"));
    REQUIRE(validator::IsUnixPath("../lenna_sharp.bmp"));
    REQUIRE(validator::IsUnixPath("../../../user/blur.bmp"));

    REQUIRE(!validator::IsUnixPath("lenna"));
    REQUIRE(!validator::IsUnixPath("./home/input"));
    REQUIRE(!validator::IsUnixPath(".bmp"));
    REQUIRE(!validator::IsUnixPath(" .bmp"));
    REQUIRE(!validator::IsUnixPath("/.bmp"));
    REQUIRE(!validator::IsUnixPath("/folder/.bmp"));
    REQUIRE(!validator::IsUnixPath(" "));
    REQUIRE(!validator::IsUnixPath(""));
}

TEST_CASE("TEST VALIDATOR::PARSE_TERMINAL") {
    std::vector<std::string> str_args = {"./image_processor", "lenna.bmp", "lenna.bmp", "-gs", "-blur", "10", "-crop",
                                         "30", "40", "-pixel", "50"};
    std::vector<char*> args(str_args.size());

    for (size_t i = 0; i < args.size(); ++i) {
        args[i] = str_args[i].data();
    }

    std::queue<FilterArguments> valid_res;

    valid_res.push(FilterArguments("-gs", {}));
    valid_res.push(FilterArguments("-blur", {"10"}));
    valid_res.push(FilterArguments("-crop", {"30", "40"}));
    valid_res.push(FilterArguments("-pixel", {"50"}));

    auto res = validator::ParseTerminal(static_cast<int>(args.size()), args);

    REQUIRE(valid_res == res);
}

TEST_CASE("TEST GRAYSCALE") {
    const size_t img_size = 5;

    const double half = 0.5;
    Matrix init = Matrix(img_size, std::vector<Pixel>(img_size, Pixel{half, 1, half}));

    const double res_val = 0.7935;
    Matrix valid(img_size, std::vector<Pixel>(img_size, {res_val, res_val, res_val}));

    Image image(img_size, img_size);
    image.SetMatrix(init);

    std::vector<std::string> f_args = {};
    GrayscaleFilter gs(f_args);
    gs.Make(image);

    RequireMatrices(image.GetMatrix(), valid);
}

TEST_CASE("TEST NEGATIVE") {
    const size_t img_size = 5;

    Matrix init = Matrix(img_size, std::vector<Pixel>(img_size, Pixel{0, 0, 0}));
    Matrix valid(img_size, std::vector<Pixel>(img_size, {1, 1, 1}));

    Image image(img_size, img_size);
    image.SetMatrix(init);

    std::vector<std::string> f_args = {};
    NegativeFilter neg(f_args);
    neg.Make(image);

    RequireMatrices(image.GetMatrix(), valid);
}

TEST_CASE("TEST SHARPENING") {
    const size_t img_size = 5;

    Matrix init = Matrix(img_size, std::vector<Pixel>(img_size, Pixel{0, 0, 0}));
    init[2][2] = Pixel{1, 1, 1};

    Matrix valid(img_size, std::vector<Pixel>(img_size, {0, 0, 0}));
    valid[2][2] = Pixel{1, 1, 1};

    Image image(img_size, img_size);
    image.SetMatrix(init);

    std::vector<std::string> f_args = {};
    SharpFilter sharp(f_args);
    sharp.Make(image);

    RequireMatrices(image.GetMatrix(), valid);
}

TEST_CASE("TEST 3D") {
    const size_t img_size = 5;
    const double half = 0.5;

    Matrix init = Matrix(img_size, std::vector<Pixel>(img_size, Pixel{0, 0, 0}));
    init[2][2] = Pixel{1, 1, 1};

    Matrix valid(img_size, std::vector<Pixel>(img_size, {0, 0, 0}));
    valid[2][1] = Pixel{0, half, 1};
    valid[2][3] = Pixel{1, half, 0};

    Image image(img_size, img_size);
    image.SetMatrix(init);

    std::vector<std::string> f_args = {"1"};
    ThirdDimFilter tdf(f_args);
    tdf.Make(image);

    RequireMatrices(image.GetMatrix(), valid);
}
