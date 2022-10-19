#pragma once
#include <cstdint>
#include <vector>

class Image {
public:
    struct Color {
        u_int8_t R = 0;
        u_int8_t G = 0;
        u_int8_t B = 0;
    };

    Image(int w, int h);
    Color& GetPixel(int x, int y);
    Color GetPixel(int x, int y) const;
    void Set(int x, int y, u_int8_t R, u_int8_t G, u_int8_t B);
    void SetByOther(int x, int y, Image::Color other_color);
    void ResizeField(int x, int y);
    std::vector<std::vector<Image::Color>> GetField();
    void SetField(std::vector<std::vector<Image::Color>> other);

    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    std::vector<std::vector<Color>> field_;
};