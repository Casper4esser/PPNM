// kommentarerne er for min egen læring og ikke til nogen, som læser koden.
#pragma once
#include "vector.h"
#include <string>
#include <iostream>
#include <vector>
#include <functional>

namespace pp
{
    struct matrix
    {
        // en matrix laves som en vektor af vektorer.
        std::vector<pp::vector> columns;
        matrix() = default;
        matrix(int n, int m) : columns(m, pp::vector(n)) {}
        matrix(const matrix &other) = default;
        matrix(matrix &&other) = default;

        matrix &operator=(const matrix &other) = default;
        matrix &operator=(matrix &&other) = default;

        inline double &operator()(int i, int j) { return columns[j][i]; }

        // inline double &operator[](int i, int j) { return cols[j][i]; }

        inline const double &operator()(int i, int j) const { return columns[j][i]; }

        // inline const double &operator[](int i, int j) { return cols[j][i]; }

        inline vector &operator[](int i) { return columns[i]; }

        inline const vector &operator[](int i) const { return columns[i]; }

        void resize(int n, int m);

        inline int rows() const { return columns[0].size(); }

        inline int cols() const { return columns.size(); }

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
}