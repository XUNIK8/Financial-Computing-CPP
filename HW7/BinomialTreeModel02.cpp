#include "BinomialTreeModel02.h"
#include <iostream>
#include <cmath>

using namespace std;

namespace fre{

    double BinomialTreeModel::RiskNeutProb() const
    {
        return (R-D)/(U-D);
    }
    
    double BinomialTreeModel::CalculateAssetPrice(int n, int i) const
    {
        return S0*pow(U,i)*pow(D,n-i);
    }
    
    void BinomialTreeModel::UpdateBinomialTreeModel(double S0_, double U_, double D_, double R_)
    {
        S0=S0_; U=U_; D=D_; R=R_;
    }
    
    int BinomialTreeModel::GetInputData()
    {
        cout << "Enter S0: "; cin>>S0;
        cout << "Enter U: "; cin>>U;
        cout << "Enter D: "; cin>>D;
        cout << "Enter R: "; cin>>R;
        //Make sure that 0<S0, -1<D<U, -1<R
        if (S0<=0.0 || U<=-1.0 || D<=-1.0 || U<=D || R<=-1.0)
        {
            cout << "Illegal Data Ranges" << endl;
            cout << "Terminating Program" << endl;
            return -1;
        }
        //Check for Arbitrage
        if (R>=U || R<=D)
        {
            cout << "Arbitrage Opportunity Exists" << endl;
            cout << "Terminating Program" << endl;
            return -1;
        }
        cout << "Input Data Checked" << endl;
        cout << "There is no arbitrage" << endl << endl;
        return 0;
    }
    
    int BinomialTreeModel::ValidateInputData() const
    {
        if (S0<=0.0 || U<=0.0 || D<=0.0 || U<=D || R<=0.0)
        {
            cout << "Illegal Data Ranges" << endl;
            cout << "Terminating Program" << endl;
            return -1;
        }

        if (R>=U || U<=D)
        {
            cout << "Arbitrage Opportunity Exists" << endl;
            cout << "Terminating Program" << endl;
            return -1;
        }
        cout << "Input Data Checked" << endl;
        cout << "There is no arbitrage" << endl << endl;
        return 0;
    }

}