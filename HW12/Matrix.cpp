#include "Matrix.h"
#include <cmath>
using namespace std;
namespace fre {
    Vector operator-(const Vector& V, const double& a)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j]-a;
        return U;
    }
    
    Vector operator/(const Vector& V, const Vector& W)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j]/W[j];
        return U;
    }

    Vector operator*(const Matrix& C, const Vector& V)
    {
        int d = (int)C.size();
        Vector W(d);
        for (int j = 0; j < d; j++)
        {
            W[j] = 0.0;
            for (int l = 0; l < d; l++) W[j] = W[j] + C[j][l] * V[l];
        }
        return W;
    }

    Vector operator+(const Vector& V, const Vector& W)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
        return U;
    }

    Vector operator+(const double& a, const Vector& V)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = a + V[j];
        return U;
    }

    Vector operator*(const double& a, const Vector& V)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = a * V[j];
        return U;
    }

    Vector operator*(const Vector& V, const Vector& W)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = V[j] * W[j];
        return U;
    }

    Vector exp(const Vector& V)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j = 0; j < d; j++) U[j] = std::exp(V[j]);
        return U;
    }

    double operator^(const Vector& V, const Vector& W)
    {
        double sum = 0.0;
        int d = (int)V.size();
        for (int j = 0; j < d; j++) sum = sum + V[j] * W[j];
        return sum;
    }

    // overload cout for vector, cout every element in the vector
    ostream& operator<<(ostream& out, Vector& V)
    {
        for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
            out << *itr << "   ";
        out << endl;
        return out;
    }

    ostream& operator<<(ostream& out, Matrix& W)
    {
        for (Matrix::iterator itr = W.begin(); itr != W.end(); itr++)
            out << *itr;    // Use ostream & operator<<(ostream & out, Vector & V)
        out << endl;
        return out;
    }
}


