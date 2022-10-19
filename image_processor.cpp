#include "filters.h"
#include "iostream"
#include "parser.h"
#include "Filter_factory.h"

int main(int argc, char* argv[]) {
    try {
        Parser p;
        p.Parse(argc, argv);
        Filter_factory f;
        f.Run(p);
    } catch (const std::exception& e) {
        std::cout << "something went wrong" << std::endl;
    }

    return 0;
}