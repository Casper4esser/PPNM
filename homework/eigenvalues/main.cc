#include "vector.h"
#include "matrix.h"
#include "EVD.h"
#include <iostream>

int main()
{
    int n = 4;

    pp::matrix A = pp::generate_random_matrix(n, n);
    A = A + A.transpose(); // gør matricen symmetrisk

    A.print("A: ");

    pp::EVD evd(A);

    pp::matrix D(n, n);

    for (int i = 0; i < n; i++)
    {
        D(i, i) = evd.w[i];
    }

    pp::matrix VT = evd.V.transpose();
    pp::matrix VT_A_V = VT * A * evd.V;
    bool VT_A_V_is_D = pp::approx(VT_A_V, D);

    pp::matrix V_D_VT = evd.V * D * VT;
    bool V_D_VT_is_A = pp::approx(V_D_VT, A);

    pp::matrix VT_V = VT * evd.V;
    bool VT_V_is_I = pp::approx(VT_V, pp::eye(n));

    pp::matrix V_VT = evd.V * VT;
    bool V_VT_is_I = pp::approx(V_VT, pp::eye(n));

    std::cout << "Er V^T * A * V = D? : " << VT_A_V_is_D << std::endl;
    std::cout << "Er V * D * V^T = A? : " << V_D_VT_is_A << std::endl;
    std::cout << "Er V^T * V = I? : " << VT_V_is_I << std::endl;
    std::cout << "Er V * V^T = I? : " << V_VT_is_I << std::endl;
}
