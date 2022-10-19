#include <iostream>
#include "filters.h"
#include "Filter_factory.h"
#include "bmp.h"
void Filter_factory::Run(Parser parser) {
    Image img = LoadBMP(parser.input_path);
    Image& im = img;

    for (int i = 0; i < parser.pipeline.size(); ++i) {
        if (parser.pipeline[i].filter_name == "-crop") {
            try {
                Crop c;
                int w = std::stoi(parser.pipeline[i].params[0]);
                int h = std::stoi(parser.pipeline[i].params[1]);
                c.Apply(im, w, h);
            } catch (const std::exception& e) {
                std::cout << "error in applying grayscale, check arguments" << std::endl;
            }

        } else if (parser.pipeline[i].filter_name == "-neg") {
            try {
                NegativeFilter n;
                n.Apply(im);
            } catch (const std::exception& e) {
                std::cout << "error in applying negative, check arguments" << std::endl;
            }

        } else if (parser.pipeline[i].filter_name == "-sharp") {
            try {
                Sharp s;
                s.Apply(im);
            } catch (const std::exception& e) {
                std::cout << "error in applying sharp, check arguments" << std::endl;
            }

        } else if (parser.pipeline[i].filter_name == "-edge") {
            try {
                Edge e;
                int t = std::stoi(parser.pipeline[i].params[0]);
                e.Apply(im, t);
            } catch (const std::exception& e) {
                std::cout << "error in applying edge, check arguments" << std::endl;
            }
        } else if (parser.pipeline[i].filter_name == "-gs") {
            try {
                GrayScale g;
                g.Apply(im);
            } catch (const std::exception& e) {
                std::cout << "error in applying grayscale, check arguments" << std::endl;
            }

        } else if (parser.pipeline[i].filter_name == "-mir") {
            try {
                Miror m;
                m.Apply(im);
            } catch (const std::exception& e) {
                std::cout << "error in applying miror, check arguments" << std::endl;
            }

        } else {
            std::cout << "error in applying filter, check arguments" << std::endl;
        }
    }
    SaveBMP(img, parser.output_path);
}
