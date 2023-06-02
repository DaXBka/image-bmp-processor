#pragma once

#include "Filters/Filter.h"

class NegativeFilter : public Filter {
public:
    explicit NegativeFilter(const std::vector<std::string>& args);
    void Make(Image& image) override;
};
