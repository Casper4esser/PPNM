#include <cmath>
#include <iostream>

// der er ingen argc eller argv[] i denne metode, fordi vi ikke læser noget fra keyboardet.
int main()
{
    double x;
    while (std::cin >> x)
    {
        std::cout << x << " " << std::sin(x) << " " << std::cos(x) << std::endl;
    }

    exit(EXIT_SUCCESS);
}