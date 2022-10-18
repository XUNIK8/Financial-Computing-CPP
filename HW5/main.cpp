#include <iostream>
#include <iomanip>
#include "BinomialTreeModel02.h"
#include "Option05.h"
#include "DoubDigitOpt.h"
#include "StrangleOpt.h"
#include "ButterflyOpt.h"

using namespace std;
using namespace fre;

int main()
{
    int N=8;
    double U=1.15125, D=0.86862, R=1.00545;
    double S0=106.00, K1=100.00, K2=110.00;
    
    BinomialTreeModel Model(S0,U,D,R);
    
    DoubDigitOpt DoubDigitOpt(N,K1,K2);
    OptionCalculation doubledigitCalculation(&DoubDigitOpt);
    cout << "European Double Digit Option Price = " << fixed << setprecision(2) << doubledigitCalculation.PriceByCRR(Model) << endl;
    
    StrangleOpt StrangleOpt(N,K1,K2);
    OptionCalculation strangleCalculation(&StrangleOpt);
    cout << "European Strangle Option Price = " << fixed << setprecision(2) << strangleCalculation.PriceByCRR(Model) << endl;
    
    ButterflyOpt ButterflyOpt(N,K1,K2);
    OptionCalculation butterflyCalculation(&ButterflyOpt);
    cout << "European Butterfly Option Price = " << fixed << setprecision(2) << butterflyCalculation.PriceByCRR(Model) << endl;
    
    // Call call(N,K);
    // OptionCalculation callCalculation(&call);
    // cout << "European Call Option Price = " << fixed << setprecision(2) << callCalculation.PriceByCRR(Model) << endl;
    
    // Put put(N,K);
    // OptionCalculation putCalculation(&put);
    // cout << "European Put Option Price = " << fixed << setprecision(2) << putCalculation.PriceByCRR(Model) << endl;
    
    // BullSpread bullspread(N,K1,K2);
    // OptionCalculation bullspreadCalculation(&bullspread);
    // cout << "European Bull Spread Option Price = " << fixed << setprecision(2) << bullspreadCalculation.PriceByCRR(Model) << endl;
    
    // BearSpread bearspread(N,K1,K2);
    // OptionCalculation bearspreadCalculation(&bearspread);
    // cout << "European Bear Spread Option Price = " << fixed << setprecision(2) << bearspreadCalculation.PriceByCRR(Model) << endl;
    
    return 0;
    
}

/* Results:

European Double Digit Option Price = 0.26
European Strangle Option Price = 28.39
European Butterfly Option Price = 1.04

*/