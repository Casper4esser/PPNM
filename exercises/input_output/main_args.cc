#include <vector>
#include <string>
#include <cmath>
#include <iostream>

// int argc er hvor mange ord der er (ord er separeret af mellemrum). char* argv[] er listen med ord.
// F.eks. "./main -n 5 -n 10". Her er argc = 5 og argv[0] = "./main", argv[1] = "-n", argv[2] = "5" osv.
// I forløkken, går programmet igennem hvert ord i argv.
// så ser programmet om der står "-n" (if(arg=="-n")). Hvis der gør, tager programmet den næste string og gør til et tal (std::stod(argv[i+1])).
// push_back tager så dette tal og sætte ind i bunden af min vektor, som blev lavet med std::vector<doubles> numbers.
int main(int argc, char *argv[])
{
    std::vector<double> numbers;
    for (int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-n" && i + 1 < argc)
            numbers.push_back(std::stod(argv[i + 1]));
    }

    // auto n gør at den selv genkender hvad numbers er. numbers består af doubles (std::vector<doubles>). 
    // Det ville derfor være det samme som at skrive for(double n : numbers).
    for (auto n : numbers)
        std::cout << n << " " << std::sin(n) << " " << std::cos(n) << std::endl;
    
    exit(EXIT_SUCCESS); // samme som return 0
}