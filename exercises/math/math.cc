#include <cmath>
#include <complex>
#include <iostream>
#include "sfuns.h"

using complex = std::complex<double>;           // navngiver typen std::complex<double> som complex, 
                                                // så jeg i stedet bare kan skrive complex foran ting
constexpr double PI = 3.14159265358979324;      // const vil sige, variablen ikke ændrer sig. 
                                                // expr vil sige værdien ikke slåes op og findes hver gang, den skal bruges. 
                                                // Den står der bare som et tal, hver gang jeg skriver pi.
constexpr double EULER = 2.71828182845904523;
constexpr complex I = complex(0, 1);

int main(){
    std::cout << "sqrt(2) = " << std::sqrt(2) << "\n";
    std::cout << "2^(1/5) = " << std::pow(2, 1.0 / 5.0) << "\n";
    std::cout << "e^pi = " << std::pow(EULER, PI) << "\n";
    std::cout << "e^i = " << std::pow(EULER, I) << "\n";
    std::cout << "pi^e = " << std::pow(PI, EULER) << "\n";
    std::cout << "pi^i = " << std::pow(PI, I) << "\n";
    std::cout << "i^i = " << std::pow(I, I) << "\n";
    std::cout << "log(I) = " << std::log(I) << "\n";

    for (int x = 1; x <= 10; ++x){
        std::cout << "Gamma(" << x << ") = " << sfuns::fgamma(x) << "\n";
    }

    return 0;
}

