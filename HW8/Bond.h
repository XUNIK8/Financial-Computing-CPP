#pragma once
#include <cmath>

namespace fre{
    class Bond{
        private:
            double F, T, C;
            
        public:
            Bond(double F_, int T_, double C_):F(F_), T(T_), C(C_){}
            ~Bond(){}
            
            double Value(double y)
            {
                double P = F * exp(-y*T);
                
                for (int t = 1; t <= T; t++)
                {
                    P += C * exp(-y*t);
                }
                return P;
            }
            
            double Derive(double y)
            {
                double P = -T * F * exp(-y*T);
                
                for (int t = 1; t <= T; t++)
                {
                    P += -C * t * exp(-y*t);
                }
                return P;
            }
        };
}
