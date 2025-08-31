// for miscellaneous maths operations e.g. multiply matrix

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "../Matrix.hpp"

namespace utils
{
    class Math
    {
        public: 
            static void multiplyMatrix(Matrix *a, Matrix *b, Matrix *c); // c is the matrix that is returned back
        private:
    };
}
