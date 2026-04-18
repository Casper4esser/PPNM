// kommentarerne er for min egen læring
// og ikke til nogen, som læser koden.
#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <iomanip>
#include "approx.h"

int main()
{
    float f = 1.0f; // f'et bag 1.0 gør at det er en float og ikke en double
    // Vi gør (1.0f + f) til en float, selvom det allerede er
    // en sum af to floats, fordi CPU'en åbenbart kan finde på
    // at gemme regnestykker af floats i 80 bit i stedet for 32 bit.
    while ((float)(1.0f + f) != 1.0f)
    {
        f /= 2.0f; // halverer f indtil maskinen synes f = 1.0f
    }
    f *= 2.0f;

    double d = 1.0;
    while ((double)(1.0 + d) != 1.0)
    {
        d /= 2.0;
    }
    d *= 2.0;

    long double l = 1.0L;
    while ((long double)(1.0L + l) != 1.0L)
    {
        l /= 2.0L;
    }
    l *= 2.0L;

    std::cout << "1. \n \n";

    // Nedenstående gør det samme som std::cout << "float eps = " << f << "\n";
    // %g skaber et hul. Dvs. den sætter find i dette hul.
    std::printf("float eps = %g\n", f);
    std::printf("double eps = %g\n", d);
    std::printf("long double eps = %Lg\n", l);

    std::cout << "float eps fra <limits> header: " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "double eps fra <limits> header: " << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "long double eps fra <limits> header: " << std::numeric_limits<long double>::epsilon() << "\n";

    std::cout << "2^(-52) = " << std::pow(2, -52) << "\n";
    std::cout << "2^(-23) = " << std::pow(2, -23) << "\n \n";

    std::cout << "2. \n \n";

    double epsilon = std::pow(2, -52);
    double tiny = epsilon / 2;
    double a = 1 + tiny + tiny;
    double b = tiny + tiny + 1;
    std::cout << "a == b ? " << (a == b ? "true" : "false") << "\n";
    std::cout << "a > 1 ? " << (a > 1 ? "true" : "false") << "\n";
    std::cout << "b > 1 ? " << (b > 1 ? "true" : "false") << "\n";

    std::string tekst = R"(Computeren regner fra venstre mod højre. Dvs. a = (1 + tiny) + tiny. 
Da tiny er mindre end maksinpræcisionen bliver (1 + tiny) bare 1.0. 
Derefter regner den 1.0 + tiny som også bare er 1.0. Så a er eksakt lig 1.0.
b regnes som (tiny + tiny) + 1. tiny er gemt som bits i tre dele: Et fortegn, en eksponent og en mantisse. 
Da eksponenten er den samme i (tiny + tiny) kan den godt lægge disse tal sammen inden for maskinpræcision.
Så tiny + tiny = epsilon og dermed er b = epsilon + 1.0 som er lidt større end 1.0.)";

    std::cout << tekst << "\n \n";

    // std::fixed gør at cout altid bruger decimaltal og ikke videnskabelig notation.
    // std::setprecision(17) gør at der er 17 decimaler
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "tiny = " << tiny << "\n";
    std::cout << "1 + tiny + tiny = " << a << "\n";
    std::cout << "tiny + tiny + 1 = " << b << "\n \n";
    
    std::cout << "3 \n \n";

    double d1 = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
    double d2 = 8 * 0.1;

    std::cout << "d1 == d2 ? " << (d1 == d2 ? "true" : "false") << "\n";

    std::cout << "d1 = " << d1 << "\n";
    std::cout << "d2 = " << d2 << "\n \n";

    std::cout << "4. \n \n";
    std::cout << "d1 == d2 ? " << (utils::approx(d1, d2) ? "true" : "false");

    return 0;
}
