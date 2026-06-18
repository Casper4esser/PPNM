// kommentarerne er for min egen læring og ikke til nogen, som læser koden.
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <functional>

namespace pp
{
    struct vector
    {
        std::vector<double> data;

        // default constructor. Hvis jeg laver en vektor uden at give input,
        // opretter den en "tom" vektor
        vector() = default;

        // Constructor. Laver vektor af størrelse n
        vector(int n) : data(n) {}

        // Lader os oprette en vektor med en liste {3, 2, 4}
        vector(std::initializer_list<double> list) : data(list) {}

        vector(const vector &) = default;

        vector(vector &&) noexcept = default;

        vector &operator=(const vector &) = default;

        vector &operator=(vector &&) noexcept = default;

        // auto n(){return std::views::iota(0,size());}
        void resize(int n) { data.resize(n); }
        inline int size() const { return data.size(); }
        inline double &operator[](int i) { return data[i]; }
        inline const double &operator[](int i) const { return data[i]; }

        vector &operator+=(const vector &other);
        vector &operator-=(const vector &other);
        vector &operator*=(double c);
        vector &operator/=(double c);

        void print(std::string s = "") const;

        friend std::ostream &operator<<(std::ostream &, const vector &);

        vector map(std::function<double(double)> f) const;

    }; // vector

    vector operator+(vector a, const vector &b);
    vector operator-(vector a, const vector &b);
    vector operator*(vector a, double c);
    vector operator*(double c, vector a);
    vector operator/(vector a, double c);
    vector operator-(vector a);

    double dot(const vector &a, const vector &b);
    double norm(const vector &a);
    bool approx(const vector &a, const vector &b, double acc = 1e-6, double eps = 1e-6);
    vector generate_random_vector(const int n);

}