#pragma once
#include "BinomialTreeModel02.h"
#include <cmath>

namespace fre{
    class BlackScholesModel{
        
        private:
            double S0,r,sigma,T;
            int N;
            
        public:
            BlackScholesModel(double S0_,double r_,double sigma_,double T_, int N_):S0(S0_),r(r_),sigma(sigma_),T(T_),N(N_){}
            ~BlackScholesModel(){}
            
            double calc_U();
            
            double calc_D();
                
            double calc_R();
                    
            BinomialTreeModel BinomialTree();
        };
}