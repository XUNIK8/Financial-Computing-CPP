#pragma once

#include "Option05.h"

namespace fre {
    class StrangleOpt : public EurOption
    {
        private:
            double K1;
            double K2;
        public:
            StrangleOpt(int N_, double K1_, double K2_): EurOption(N_), K1(K1_), K2(K2_) {}
            ~StrangleOpt() {}
            
            double Payoff(double z) const;
    };
}