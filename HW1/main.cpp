// OptionPricer02.cpp
//

#include "BinomialTreeModel.h"
#include "Option01.h"
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

    double optionPrice = PriceByCRR(s0, u, d, r, N, k);
    cout << "European call option price = " << fixed << setprecision(2) << optionPrice << endl;
    
    return 0;
}
/*
HW1:
European call option price = 21.68

*/
