#include "Option02.h"
#include "BinomialTreeModel.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
    int Fact(int N)
    {
        if (N <= 1)
            return 1;
        else 
            return N*Fact(N-1);
    }
    
    double PriceByCRR(double S0, double U, double D, double R, unsigned int N, double K, double(*payoff)(double z, double K))
    {
        double q = RiskNeutProb(U, D, R);
        double Price[N+1];
        double H0 = 0.0;
        
        for (unsigned int i = 0; i < sizeof(Price) / sizeof(Price[0]); i++)
            Price[i] = 0.0;

        for (unsigned int i = 0; i <= N; i++)
        {
            Price[i] = payoff(CalculateAssetPrice(S0, U, D, N, i), K);
            // Modified CRR
            H0 += Fact(N)*pow(q,i)*pow(1-q,N-i)*Price[i]/Fact(i)/Fact(N-i);
            // Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / R;
        }
        return H0/pow(R,N);
    }

    // Definition of Payoff functions
    double CallPayoff(double z, double K)
    {
        if (z > K) 
            return z - K;
        else
            return 0.0;
    }
    
    double PutPayoff(double z, double K)
    {
        if (z < K)
            return K - z;
        else
            return 0.0;
    }
    
    double DigitCallPayoff(double z,double K)
    {
        if (z > K)
            return 1.0;
        else
            return 0.0; 
    }
    
    double DigitPutPayoff(double z, double K)
    {
        if (z < K)
            return 1.0;
        else
            return 0.0;
    }
}
