#pragma once
#include "image.h"

using matrix = std::vector<std::vector<int>>;

class BaseFilter {
public:
    virtual void Apply(Image& img) = 0;
};

class MatrixBaseFilter : BaseFilter {
public:
    void Apply(Image& image) override;
    void Apply(Image& image, matrix);
};

class NegativeFilter : BaseFilter {
public:
    void Apply(Image& image) override;
};

class GrayScale : BaseFilter {
public:
    void Apply(Image& image) override;
};

class Sharp : MatrixBaseFilter {
public:
    void Apply(Image& image) override;

private:
    matrix data_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};

class Edge : MatrixBaseFilter {
public:
    void Apply(Image& image) override;
    void Apply(Image& image, int treshold);

private:
    matrix data_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
};

class Crop : BaseFilter {
public:
    void Apply(Image& image) override;
    void Apply(Image& image, int x, int y);
};

class Miror : BaseFilter {
public:
    void Apply(Image& image) override;
};
