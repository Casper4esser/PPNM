// Kommentarerne er for min egen læring og ikke til nogen, som læser koden.

#include "vec.h"
#include <string>
#include <iostream>
#include <cmath>

// hjælpefunktion til approx for vec
namespace
{
    bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9)
    {
        double diff = std::abs(a - b);
        if (diff <= acc)
            return true;
        double max_ab = std::max(std::abs(a), std::abs(b));
        return diff <= eps * max_ab;
    }
}

// en funktion består af tre dele:
// [Hvad spytter jeg ud?] [Hvad hedder jeg?] ([Hvad skal jeg bruge som input])
// [Hvad spytter jeg ud]: vec&. Dvs. funktionen giver mig en lvalue reference. Det svarer til et alias til noget.
// [Hvad hedder jeg]: vec::operator+=. Navnet på operatoren i vec.h.
// [Hvad skal jeg bruge som input]: const vec& other. Funktionen skal bruge et alias til en anden vektor, som internt i funktionen kaldes for "other".
// Der bliver returneret *this. this er en pointer til, hvorhenne en vektor ligger. Her er en mere teknisk forklaring:
// hvis man skriver v1 += v2, så er v1 24 bytes i hukommelsen, som ligger ved adressen 0x10A. x ligger på 0x10A, y ligger 8 bytes længere henne og z ligger 8 bytes længere henne igen.
// funktionen vec& vec::operator+=(const vec& other) ses af compileren praktisk set som vec& operator+=(vec* this, const vec& other). * foran vec er en pointer og en pointer er et heltal, som er en hukommelsesadresse.
// Når man skriver v1 += v2 ser compileren det som operator+=(&v1, v2). &v1 svarer vist til vec* this, så &v1 er adressen til v1.
// Så når vi skriver v1 += v2, tager funktionen adressen på v1 og adressen på v2 som input. Den læser så de 24 bytes på adressen ved v2 og lægger dem til de 24 bytes på adressen ved v1.
// funktionen returnerer så adressen på v1. Denne adresse er den samme som i starten, men nu er bytesene ændret.
// Hvis man i stedet skrev vec vec::operator+=(const vec other) altså uden references, så ville funktionen tage de 24 bytes fra v1 og de 24 bytes fra v2 og midlertidigt gemme dem. Så ville den lægge dem sammen og returnere 24 bytes.
// Der bliver altså oprettet 48 bytes midlertidigt frem for 0 bytes. Derfor bruger vi references.
vec &vec::operator+=(const vec &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

vec &vec::operator-=(const vec &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

vec &vec::operator*=(double s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

vec &vec::operator/=(double s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

void vec::print(const std::string &s) const
{
    std::cout << s << x << "" << y << "" << z << std::endl;
}

// Denne operator fungerer ved, at hvis vi skriver v3 = v1 + v2, så læser compileren det som v3 = operator+(v1, &v2).
// Den gemmer midlertidigt 24 bytes for v1. Så finder den adressen for v2, læser bytesene, lægger dem til v1 og returnerer den nye v1.
// Her skriver man ikke vec operator+(vec& a, const vec &b), for så ville computeren finde bytesene for v1 og overskrive dem, så efter vi har kørte v3 = v1 + v2, så har v1 ændret sig til v3.
vec operator+(vec a, const vec &b)
{
    a += b;
    return a;
}

vec operator-(vec a, const vec &b)
{
    a -= b;
    return a;
}

vec operator*(vec a, double s)
{
    a *= s;
    return a;
}

vec operator*(double s, vec a)
{
    a *= s;
    return a;
}

vec operator/(vec a, double s)
{
    a /= s;
    return a;
}

// Vi bruger vec& i stedet for vec, fordi vi bare kigger på bytesene og sætter et minus foran.
// Vi gør ikke noget, som måske vil ændre dem, så det hurtigere med adressen. Desuden skal a ikke ændre sig, så vi skriver const.
// Det er mest for vi sikrer os, at vi ikke ændrer på dataene ved et uheld.
// I operator+ ville vi ændre på a, så der kunne vi ikke skrive const vec& a.
vec operator-(const vec &a)
{
    return vec(-a.x, -a.y, -a.z);
}

std::ostream &operator<<(std::ostream &os, const vec &v)
{
    os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
    return os;
}

bool approx(const vec &v1, const vec &v2, double acc, double eps)
{
    return approx(v1.x, v2.x, acc, eps) &&
           approx(v1.y, v2.y, acc, eps) &&
           approx(v1.z, v2.z, acc, eps);
}

double dot(const vec &v1, const vec &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec cross(const vec &v1, const vec &v2)
{
    double x_comp = v1.y * v2.z - v1.z * v2.y;
    double y_comp = v1.z * v2.x - v1.x * v2.z;
    double z_comp = v1.x * v2.y - v1.y * v2.x;
    return vec(x_comp, y_comp, z_comp);
}

double norm(const vec &v1)
{
    return std::sqrt(dot(v1, v1));      // dot(v1, v1) virker måske ikke for komplekse tal
}
