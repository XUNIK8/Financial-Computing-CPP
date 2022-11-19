#include "PathDepOption02.h"
#include "Matrix.h"
#include <cmath>

namespace fre {
    void Rescale(SamplePath& S, double x, int k)
    {
        int m = S.size();
        for (int j = 0; j < m; j++) S[j][k] = x * S[j][k];
    }
    
    double PathDepOption::PriceByMC(MCModel& Model, long N, double epsilon)
    {
        double H = 0.0;
        int d = Model.GetS0().size();
        
        SamplePath S(m);
        Vector Heps(d);
        
        for (int j = 0; j<d; j++) Heps[j] = 0.0;
        
        for (long i = 0; i < N; i++)
        {
            Model.GenerateSamplePath(T, m, S);
            H = (i * H + Payoff(S)) / (i + 1.0);
            
            for(int k=0;k<d;k++)
            {
                Rescale(S, 1.0+epsilon,k);
                Heps[k] = (i * Heps[k] + Payoff(S)) / (i + 1.0);
                Rescale(S, 1.0/(1.0+epsilon),k);
            }
                
        }
        Price = std::exp(-Model.GetR() * T) * H;
        delta = ((std::exp(-Model.GetR() * T) * Heps) - Price) / (epsilon*Model.GetS0());
        return Price;
    }

    double ArthmAsianCall::Payoff(const SamplePath& S) const
    {
        double Ave = 0.0;
        int d = S[0].size();
        Vector one(d);
        for (int i = 0; i < d; i++) one[i] = 1.0;
        for (int k = 0; k < m; k++)
        {
            Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
        }
        if (Ave < K) return 0.0;
        return Ave - K;
    }
}
