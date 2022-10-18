#pragma once

#include "Option05.h"

namespace fre {
    class DoubDigitOpt : public EurOption
    {
        private:
            double K1;
            double K2;
        public:
            DoubDigitOpt(int N_, double K1_, double K2_): EurOption(N_), K1(K1_), K2(K2_) {}
            ~DoubDigitOpt() {}
            
            double Payoff(double z) const;
    };
}