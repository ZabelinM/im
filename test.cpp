#include "test.h"
#include "iostream"

void Test(std::string path) {
    //    TestCrop(path);
    TestNegative(path);
}

void TestCrop(std::string path) {
    bool result = true;
    int exit_code = 0;
    try {
        Image img = LoadBMP("path");
        Image& im = img;

        Crop c;

        c.Apply(im, 2500, 35000);
        if (im.GetWidth() != 2048 || im.GetHeight() != 2048) {
            result = false;
            exit_code = 1;
        }

        c.Apply(im, 1500, 2000);
        if (im.GetWidth() != 1500 || im.GetHeight() != 2000) {
            result = false;
            exit_code = 2;
        }

        c.Apply(im, 1000, 1000);
        if (im.GetWidth() != 1000 || im.GetHeight() != 1000) {
            result = false;
            exit_code = 3;
        }

        c.Apply(im, 700, 300);
        if (im.GetWidth() != 700 || im.GetHeight() != 300) {
            result = false;
            exit_code = 4;
        }

    } catch (const std::exception& e) {
        result = false;
        exit_code = -1;
    }

    if (result) {
        std::cout << "Crop work correct" << std::endl;
    } else {
        std::cout << "Crop DOES NOT work correct, exit code = " << exit_code << std::endl;
    }
}

void TestNegative(std::string path) {
    bool result = true;
    int exit_code = 0;
    try {
        Image img = LoadBMP("path");
        Image& im = img;
        NegativeFilter n;

        u_int8_t col_r = img.GetPixel(0, 0).R;
        n.Apply(im);
        if (255 - col_r != img.GetPixel(0, 0).R) {
            result = false;
            exit_code = 1;
        }
        n.Apply(im);
        if (col_r != img.GetPixel(0, 0).R) {
            result = false;
            exit_code = 2;
        }
    } catch (const std::exception& e) {
        result = false;
        exit_code = -1;
    }

    if (result) {
        std::cout << "Negative work correct" << std::endl;
    } else {
        std::cout << "Negative DOES NOT work correct, exit code = " << exit_code << std::endl;
    }
}
