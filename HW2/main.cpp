// OptionPricer02.cpp
//

#include "BinomialTreeModel.h"
#include "Option02.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace fre;

int main()
{
    double u = 1.15125, d = 0.86862, r = 1.00545;
    double s0 = 106.00;
    double k = 100.00;
    const unsigned int N = 8;

    cout << "European call option price = " << fixed << setprecision(2) << PriceByCRR(s0, u, d, r, N, k, CallPayoff) << endl;
    cout << "European put option price = " << fixed << setprecision(2) << PriceByCRR(s0, u, d, r, N, k, PutPayoff) << endl;
    cout << "Digit call option price = " << fixed << setprecision(2) << PriceByCRR(s0, u, d, r, N, k, DigitCallPayoff) << endl;
    cout << "Digit put option price = " << fixed << setprecision(2) << PriceByCRR(s0, u, d, r, N, k, DigitPutPayoff) << endl;

    
    // delete [] optionPrice;
    // optionPrice = NULL
    
    return 0;
}
/*
HW2:
European call option price = 21.68
European put option price = 11.43
Digit call option price = 0.58
Digit put option price = 0.38
*/
