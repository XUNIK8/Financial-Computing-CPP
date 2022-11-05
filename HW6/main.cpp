#include <iostream>
#include <iomanip>
#include <fstream>
#include "BinomialTreeModel02.h"
#include "Option08.h"

using namespace std;
using namespace fre;

int main()
{
    int N=8;
    double U=1.15125, D=0.86862, R=1.00545;
    double S0=106.00, K=100.00;
    
    BinomialTreeModel Model(S0,U,D,R);
    
    ofstream fout;
    fout.open("Result.txt");
    
    Call call(N,K);
    OptionCalculation callCalculation(&call);
    
    BinLattice<double> CallPriceTree;
    BinLattice<double> CallXTree;
    BinLattice<double> CallYTree;
    
    fout << "European call prices by PriceByCRR:" << fixed << setprecision(2) << callCalculation.PriceByCRR(Model) << endl << endl;
    fout << "European call prices by HW6 PriceByCRR:" << fixed << setprecision(2) << callCalculation.PriceByCRR(Model,CallPriceTree,CallXTree,CallYTree) << endl << endl;
    fout << "Stock positions in replicating strategy:" << endl << endl;
    CallXTree.Display(fout);
    fout << "Money market account positions in replicating strategy:" << endl << endl;
    CallYTree.Display(fout);
    

    Put put(N,K);
    OptionCalculation putCalculation(&put);
    
    BinLattice<double> PutPriceTree;
    BinLattice<double> PutXTree;
    BinLattice<double> PutYTree;
    
    fout << "European put prices by PriceByCRR:" << fixed << setprecision(2) << putCalculation.PriceByCRR(Model) << endl << endl;
    fout << "European put prices by HW6 PriceByCRR:" << fixed << setprecision(2) << putCalculation.PriceByCRR(Model,PutPriceTree,PutXTree,PutYTree) << endl << endl;
    fout << "Stock positions in replicating strategy:" << endl << endl;
    PutXTree.Display(fout);
    fout << "Money market account positions in replicating strategy:" << endl << endl;
    PutYTree.Display(fout);

    // BinLattice<double> CallPriceTree(N);
    // BinLattice<bool> CallStoppingTree(N);
    
    // BinLattice<double> PutPriceTree(N);
    // BinLattice<bool> PutStoppingTree(N);

    // cout << "American Call Option Price = " << fixed << setprecision(2) << callCalculation.PriceBySnell(Model,CallPriceTree) << endl;
    // cout<<"American call price tree:"<<endl<<endl;
    // CallPriceTree.Display();
    // cout<<"American call exercise policy:"<<endl<<endl;
    // CallStoppingTree.Display();
    
    // cout << "American Put Option Price = " << fixed << setprecision(2) << putCalculation.PriceBySnell(Model,PutPriceTree) << endl;
    // cout<<"American put price tree:"<<endl<<endl;
    // PutPriceTree.Display();
    // cout<<"American put exercise policy:"<<endl<<endl;
    // PutStoppingTree.Display();
    
    
    return 0;
    
}
