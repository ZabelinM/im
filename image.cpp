#include "image.h"
Image::Image(int w, int h) {
    field_.resize(h, std::vector<Color>(w, {.R = 255, .G = 255, .B = 255}));
}

Image::Color& Image::GetPixel(int x, int y) {
    return field_[x][y];
}

Image::Color Image::GetPixel(int x, int y) const {
    return field_[x][y];
}

size_t Image::GetWidth() const {
    return field_.size();
}

size_t Image::GetHeight() const {
    return field_.front().size();
}
void Image::Set(int x, int y, u_int8_t R, u_int8_t G, u_int8_t B) {
    field_[x][y].R = R;
    field_[x][y].G = G;
    field_[x][y].B = B;
}
void Image::ResizeField(int x, int y) {
    for (int i = 0; i < this->GetHeight(); ++i) {
        this->field_[i].resize(y);
    }
    this->field_.resize(x);
}
std::vector<std::vector<Image::Color>> Image::GetField() {
    return this->field_;
}
void Image::SetField(std::vector<std::vector<Image::Color>> other) {
    this->field_ = other;
}
void Image::SetByOther(int x, int y, Image::Color other_color) {
    this->field_[x][y] = other_color;
}
