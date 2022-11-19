#include "PathDepOption.h"
#include "EurCall.h"
#include <cmath>
#include <iostream>

namespace fre {
    void Rescale(SamplePath& S, double x)
    {
        int m = S.size();
        for (int j = 0; j < m; j++) S[j] = x * S[j];
    }

    double PathDepOption::PriceByMC(const MCModel& Model, long N, double epsilon)
    {
        double H = 0.0, Hsq = 0.0, Heps = 0.0;
        SamplePath S(m);
        for (long i = 0; i < N; i++)
        {
            Model.GenerateSamplePath(T, m, S);
            H = (i * H + Payoff(S)) / (i + 1.0);
            Hsq = (i * Hsq + pow(Payoff(S), 2.0)) / (i + 1.0);
            Rescale(S, 1.0 + epsilon);
            Heps = (i * Heps + Payoff(S)) / (i + 1.0);
        }
        Price = exp(-Model.GetR() * T) * H;
        PricingError = exp(-Model.GetR() * T) * sqrt(Hsq - H * H) / sqrt(N - 1.0);
        
        delta = exp(-Model.GetR() * T) * (Heps - H) / (Model.GetS0() * epsilon);
        return Price;
    }

    double PathDepOption::PriceByVarRedMC(const MCModel& Model, long N, PathDepOption& CVOption, double epsilon)
    {
        DifferenceOfOptions VarRedOpt(T, K, m, this, &CVOption);

        Price = VarRedOpt.PriceByMC(Model, N, epsilon) + CVOption.PriceByBSFormula(Model);

        PricingError = VarRedOpt.PricingError;
        
        delta = VarRedOpt.GetDelta() + CVOption.GetDelta();
        return Price;
    }

    double ArthmAsianCall::Payoff(const SamplePath& S) const
    {
        double Ave = 0.0;
        for (int k = 0; k < m; k++) Ave = (k * Ave + S[k]) / (k + 1.0);
        if (Ave < K) return 0.0;
        return Ave - K;
    }
}
