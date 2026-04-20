// kommentarerne er for min egen læring og ikke til nogen, som læser koden

#include <string>
#include <fstream>
#include <cmath>

int main(int argc, char *argv[])
{
    // I terminalen skriver vi: ./main_file --input in.txt --output out.txt.
    // Derfor tjekker programmet først om der står "--input" eller "--output" for at se, hvad der er hvad.
    std::string infile = "", outfile = "";
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "--input" && i + 1 < argc)
            infile = argv[i + 1];
        if (arg == "--output" && i + 1 < argc)
            outfile = argv[i + 1];
    }

    // lav instances af typerne ifstream og ofstream. Disse instances har metoder såsom myinput.is_open() (er filerne blevet åbnet?)
    // og myinput >> x (tag en bid tekst i myinput, dvs. infile, og send det til variablen x).
    std::ifstream myinput(infile);
    std::ofstream myoutput(outfile);

    double x;
    if (myinput.is_open() && myoutput.is_open())
    {
        // myinput >> x fungerer ved at den læser alle tegn i myinput indtil den møder noget som ikke er en double. F.eks. en whitespace eller string.
        // Så sender den det til x. Så længe den finder gyldig tekst så er statementet true. Hvis den rammer whitespace eller string er den false. 
        while (myinput >> x)
        {
            myoutput << x << " " << std::sin(x) << " " << std::cos(x) << std::endl;
        }
    }

    myinput.close();
    myoutput.close();

    exit(EXIT_SUCCESS);
}
