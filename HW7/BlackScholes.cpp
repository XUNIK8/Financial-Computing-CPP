#include "BlackScholes.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace fre{

    double BlackScholesModel::calc_U()
    {
        return exp(sigma*sqrt(T/N)); 
    }
    
    double BlackScholesModel::calc_D()
    {
        return 1 / (exp(sigma*sqrt(T/N))); 
    }
        
    double BlackScholesModel::calc_R()
    {
        return exp(r*T/N); 
    }
    
    BinomialTreeModel BlackScholesModel::BinomialTree()
    {
        return BinomialTreeModel(S0,calc_U(),calc_D(),calc_R());
    }
        
}