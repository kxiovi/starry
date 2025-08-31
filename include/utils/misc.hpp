#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace utils
{
    class Misc
    {
    public:
        static std::vector<std::vector<double>> fetchData(std::string path);
    };
}