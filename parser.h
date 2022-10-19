#pragma once
#include <string>
#include <vector>
class Parser {
public:
    struct FilterParametrs {
        std::string filter_name;
        std::vector<std::string> params;
    };

    void Parse(int argc, char* argv[]);

    std::string input_path;
    std::string output_path;
    std::vector<FilterParametrs> pipeline;
};