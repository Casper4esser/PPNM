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

    struct matrix
    {
        // en matrix laves som en vektor af vektorer.
        std::vector<pp::vector> cols;
        matrix() = default;
        matrix(int n, int m) : cols(m, pp::vector(n)) {}
        matrix(const matrix &other) = default;
        matrix(matrix &&other) = default;

        matrix &operator=(const matrix &other) = default;
        matrix &operator=(matrix &&other) = default;

        inline double &operator()(int i, int j) { return cols[j][i]; }

        // inline double &operator[](int i, int j) { return cols[j][i]; }

        inline const double &operator()(int i, int j) const { return cols[j][i]; }

        // inline const double &operator[](int i, int j) { return cols[j][i]; }

        inline vector &operator[](int i) { return cols[i]; }

        inline const vector &operator[](int i) const { return cols[i]; }

        void resize(int n, int m);

        inline int size1() const { return cols[0].size(); }

        inline int size2() const { return cols.size(); }

        void setid();

        matrix transpose() const;

        matrix T() const { return transpose(); }

        matrix &operator+=(const matrix &B);
        matrix &operator-=(const matrix &B);
        matrix &operator*=(const double c);
        matrix &operator/=(const double c);
        matrix &operator*=(const matrix &B);
        matrix operator^(int c);
        void print(std::string s = "") const;

    }; // matrix

    matrix operator+(matrix A, const matrix &B);
    matrix operator-(matrix A, const matrix &B);
    matrix operator*(const matrix &A, const matrix &B);
    matrix operator*(matrix A, const double c);
    matrix operator*(const double c, matrix A);
    matrix operator/(matrix A, const double c);
    vector operator*(const matrix &A, const vector &v);

    matrix generate_random_matrix(const int n, const int m);
    bool approx(const matrix &A, const matrix &B, double acc = 1e-6, double eps = 1e-6);
    matrix eye(int n);

    struct qr
    {
        matrix Q;
        matrix R;

        qr(const matrix &A);
        vector solve(const vector &b) const;

        double det() const;
    }; // qr
} // pp
