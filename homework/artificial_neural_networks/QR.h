#include "vector.h"
#include "matrix.h"

namespace pp
{
    struct qr
    {
        matrix Q;
        matrix R;

        qr(const matrix &A);
        vector solve(const vector &b) const;

        double det() const;
    }; // qr
}
