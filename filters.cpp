#include "filters.h"

void NegativeFilter::Apply(Image& image) {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            u_int8_t new_r = 255 - image.GetPixel(i, j).R;
            u_int8_t new_g = 255 - image.GetPixel(i, j).G;
            u_int8_t new_b = 255 - image.GetPixel(i, j).B;
            image.Set(i, j, new_r, new_g, new_b);
        }
    }
}

void GrayScale::Apply(Image& image) {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            u_int8_t new_r =
                0.299 * image.GetPixel(i, j).R + 0.587 * image.GetPixel(i, j).G + 0.114 * image.GetPixel(i, j).B;
            image.Set(i, j, new_r, new_r, new_r);
        }
    }
}

void Crop::Apply(Image& image) {
    this->Apply(image, image.GetWidth(), image.GetHeight());
}

void Crop::Apply(Image& image, int x, int y) {
    if (x > image.GetWidth()) {
        x = image.GetWidth();
    }
    if (y > image.GetHeight()) {
        y = image.GetHeight();
    }
    image.ResizeField(x, y);
}

void MatrixBaseFilter::Apply(Image& image, std::vector<std::vector<int>> data) {
    std::vector<std::vector<Image::Color>> copy_field = image.GetField();
    int border_parametr_x = 1;
    int border_parametr_y = 1;

    for (int i = 0; i < image.GetHeight() - 1; ++i) {
        for (int j = 0; j < image.GetWidth() - 1; ++j) {
            if (i == 0 || i == image.GetHeight() - 1) {
                border_parametr_x = 0;
            } else {
                border_parametr_x = 1;
            }
            if (j == 0 || j == image.GetWidth() - 1) {
                border_parametr_y = 0;
            } else {
                border_parametr_y = 1;
            }

            int new_r = 0;
            int new_g = 0;
            int new_b = 0;

            for (int k = 0; k < data.size(); ++k) {
                for (int l = 0; l < data.front().size(); ++l) {
                    new_r += image.GetPixel(i + l - border_parametr_x, j + k - border_parametr_y).R * data[l][k];
                    new_g += image.GetPixel(i + l - border_parametr_x, j + k - border_parametr_y).G * data[l][k];
                    new_b += image.GetPixel(i + l - border_parametr_x, j + k - border_parametr_y).B * data[l][k];
                }
            }

            copy_field[i][j].R = std::min(255, std::max(0, new_r));
            copy_field[i][j].G = std::min(255, std::max(0, new_g));
            copy_field[i][j].B = std::min(255, std::max(0, new_b));
        }
    }
    image.SetField(copy_field);
}

void MatrixBaseFilter::Apply(Image& image) {
}

void Edge::Apply(Image& image) {
    this->Apply(image, 35);
}

void Edge::Apply(Image& image, int treshold) {
    GrayScale g;
    g.Apply(image);
    MatrixBaseFilter::Apply(image, this->data_);

    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            if (image.GetPixel(i, j).R > treshold) {
                image.Set(i, j, 255, 255, 255);
            } else {
                image.Set(i, j, 0, 0, 0);
            }
        }
    }
}

void Sharp::Apply(Image& image) {
    MatrixBaseFilter::Apply(image, this->data_);
}

void Miror::Apply(Image& image) {
    for (int i = 0; i < image.GetHeight() / 2 - 1; ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetByOther(image.GetWidth() / 2 - 1 - i, j, image.GetPixel(i + image.GetWidth() / 2 - 1, j));
        }
    }
}
