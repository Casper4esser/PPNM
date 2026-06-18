#include "vec.h"
#include <iostream>

int main()
{
    int n = 6;
    int m = 4;

    pp::matrix A = pp::generate_random_matrix(n, m);
    pp::vector b = pp::generate_random_vector(n);

    pp::qr my_qr(A);
    my_qr.R.print();
    
    pp::matrix QTQ = my_qr.Q.transpose() * my_qr.Q;
    bool QTQ_is_id = pp::approx(QTQ, pp::eye(m));
    std::cout << "Er Q^T * T = I? : " << QTQ_is_id << std::endl;

    pp::matrix QA = my_qr.Q * my_qr.R;
    bool QA_is_A = pp::approx(QA, A);
    std::cout << "Er Q*R = A? : " << QA_is_A << std::endl;
    

    pp::matrix B = pp::generate_random_matrix(n,n);
    pp::qr qr_B(B);
    
    pp::vector x = qr_B.solve(b);
    pp::vector Bx = B * x;
    bool Bx_is_b = pp::approx(Bx, b);
    std::cout << "Er B*x = b? : " << Bx_is_b << std::endl;
    
    double diff = pp::norm(Bx - b);
    std::cout << "Fejl i B*x - b (skal være tæt på 0): " << diff << std::endl;

    std::cout << "determinanten af R er : " << qr_B.det() << std::endl;

    return 0;
}