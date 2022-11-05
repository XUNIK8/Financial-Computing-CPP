#include <iostream>
#include <iomanip>
#include <fstream>
#include "BinomialTreeModel02.h"
#include "Option08.h"
#include "BlackScholes.h"

using namespace std;
using namespace fre;

int main()
{
    int N=8;
    double S0=106.0;
    double r=0.058;
    double sigma=0.46;
    double T=(double)9/12;
    double K=100.0;
    
    cout << setiosflags(ios::fixed) << setprecision(5);
    
    BlackScholesModel BSModel(S0,r,sigma,T,N);
    BinomialTreeModel Model = BSModel.BinomialTree();
    
    // ofstream fout;
    // fout.open("Result.txt");
    
    
    Call call(N,K);
    OptionCalculation callCalculation(&call);

    BinLattice<double> CallPriceTree(N);
    BinLattice<bool> CallStoppingTree(N);


    cout << "S0 = " << S0 << endl;
    cout << "r = " << r << endl;
    cout << "sigma = " << sigma << endl;
    cout << "T = " << T << endl;
    cout << "K = " << K << endl;
    cout << "N = " << N << endl;
    cout << endl;
    cout << "U = " << BSModel.calc_U() << endl;
    cout << "D = " << BSModel.calc_D() << endl;
    cout << "R = " << BSModel.calc_R() << endl;
    cout << endl;
    
    cout << "American Call Option Price = " << fixed << setprecision(3) << callCalculation.PriceBySnell(Model,CallPriceTree,CallStoppingTree) << endl;
    
    // cout<<"American call price tree:"<<endl<<endl;
    // CallPriceTree.Display();
    // cout<<"American call exercise policy:"<<endl<<endl;
    // CallStoppingTree.Display();
    
    // BinLattice<double> PutPriceTree(N);
    // BinLattice<bool> PutStoppingTree(N);
    
    // cout << "American Put Option Price = " << fixed << setprecision(2) << putCalculation.PriceBySnell(Model,PutPriceTree) << endl;
    // cout<<"American put price tree:"<<endl<<endl;
    // PutPriceTree.Display();
    // cout<<"American put exercise policy:"<<endl<<endl;
    // PutStoppingTree.Display();
    
    
    return 0;
    
}

/*
Output:

S0 = 106.00000
r = 0.05800
sigma = 0.46000
T = 0.75000
K = 100.00000
N = 8

U = 1.15125
D = 0.86862
R = 1.00545

American Call Option Price = 21.682
*/