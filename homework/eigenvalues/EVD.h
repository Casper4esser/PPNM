#pragma once
#include "vector.h"
#include "matrix.h"
#include <string>
#include <iostream>
#include <vector>
#include <functional>

namespace pp
{
    struct EVD
    {
        pp::vector w;
        pp::matrix V;

        static void timesJ(pp::matrix &A, int p, int q, double theta);
        static void Jtimes(pp::matrix &A, int p, int q, double theta);

        // constructor
        EVD(pp::matrix A);
    };
}
