#include "ButterflyOpt.h"

namespace fre {
    double ButterflyOpt::Payoff(double z) const
    {
        if (K1<z&&z<=((K1+K2)/2)) return z-K1;
        else if (((K1 + K2) / 2) < z&&z < K2) return K2-z;
        return 0.0;
    }
}