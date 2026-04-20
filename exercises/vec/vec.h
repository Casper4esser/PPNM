// kommentarerne er for min egen læring og ikke til nogen, som læser koden.
#pragma once
#include <string>
#include <iostream>

// Der er forskel på om funktionerne står inde i struct vec {} (member function) eller uden for (non-member function).
// Den forskel jeg forstår er, at en member-function sender this-pointeren med ind i funktionen. Derfor bør en funktion, som ændrer den vektor,
// jeg kalder den på stå inden i struct vec {}. Der er også andre grunde til, at en funktion skal være non-member.

struct vec
{
    double x, y, z;

    // initializer. Vi har defineret vec til at bestå af tre dele: x, y, z.
    // Vi siger nu, at når vi skriver vec(double input_x, double input_y, ...)
    // så skal input_x gives til x-delen af vec. Det er det, der sker i x(x)
    // (kunne have være x(input_x), hvis vi havde valgt de navne).
    vec(double x, double y, double z) : x(x), y(y), z(z) {}

    // default constructor. Siger at hvis jeg bare skriver vec v, så er det nulvektoren.
    vec() : vec(0, 0, 0) {}

    // copy constructor. &-tegnet i vec& er åbenbart en reference.
    // Så man refererer til den vektor, man vil kopiere vist nok.
    // Så er det åbenbart hurtigere at finde for computeren.
    // Default er her, at man tager x fra den gamle vektor og kopierer til den nye vektor.
    // Det samme gælder for y og z.
    vec(const vec &) = default;

    // Move constructor. && i vec&& er en R-value reference. Jeg kan ikke helt gennemskue, hvad det gør.
    // Man tager kopierer vist tingene fra den gamle vektor og sletter dem derefter, så de kun er i den nye.
    // Dermed har man flyttet vektoren.
    vec(vec &&) = default;

    // destuctor
    ~vec() = default;

    // copy assignment operator. Hvis man skriver v1 = v2,
    // så kopierer den x, y, z i v2 og giver det til v1.
    vec &operator=(const vec &) = default;

    // Move assignment operator. Hvis man skriver v1 = v2 + v3,
    // så bliver v2 + v3 en midlertidig vektor, TEMP.
    // Derefter smides TEMP ind i v1 og TEMP slettes.
    vec &operator=(vec &&) = default;

    vec &operator+=(const vec &);
    vec &operator-=(const vec &);
    vec &operator*=(double);
    vec &operator/=(double);

    // set. Ændr en vektor.
    void set(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }

    // print. s="" siger, at hvis man bare skriver v1.print(), så sætter den automatisk teksten til en tom string.
    // const til allersidst er const correctness. Den siger, at print kun vil læse x, y, z og aldrig ændre på dem.
    // Hvis const ikke var der, ville den ikke printe en vektor, der har været en const vec&.
    void print(const std::string &s = "") const;

    // std::ostream& er typen af outputtet. operator<< er navnet. Den tager en adresse på en ostream og en adresse på en const vec ind.
    // Det er vigtigt, at det kun er adressen på ostream, for ellers ville computeren prøve at gemme hele skærmen i sin hukommelse.
    // Hvorfor friend? operator<< burde stå uden for struct, men så ville den ikke kunne læse private variabler.
    // Hvis nu det var en class i stedet for struct, ville x, y, z være private (i struct er de stadig public, så jeg kunne have skrevet operator<< uden for struct{}).
    // friend giver funktionen adgang til at læse private variabler alligevel.
    friend std::ostream &operator<<(std::ostream &, const vec &);
};

vec operator+(vec, const vec &);
vec operator-(vec, const vec &);
vec operator*(vec, double);
vec operator*(double, vec);
vec operator/(vec, double);
vec operator-(const vec&);

double dot(const vec &, const vec &);
vec cross(const vec &, const vec &);

// non-member function, den ikke ændrer på vektorerne. Den kigger bare og så laver den en ny kasse. Denne kasse er en bool.
bool approx(const vec &v1, const vec &v2, double acc = 1e-6, double eps = 1e-6);
