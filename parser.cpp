#include "iostream"
#include "parser.h"

void Parser::Parse(int argc, char* argv[]) {
    if (argc > 3) {
        input_path = argv[1];
        output_path = argv[2];
        for (int i = 3; i < argc; ++i) {
            if (argv[i][0] == '-') {
                FilterParametrs parametrs;
                parametrs.filter_name = argv[i];
                ++i;
                while (i < argc && argv[i][0] != '-') {
                    parametrs.params.push_back(argv[i]);
                    ++i;
                }
                --i;
                pipeline.push_back(parametrs);
            }
        }

    } else {
        std::cout << "Available filters : Grayscale {-gs}, Negative {-neg}, Crop {-crop width height}, Edge {-edge "
                     "treschold}, Sharpening {-sharp}, Miror {-mir}"
                  << std::endl;
    }
}
