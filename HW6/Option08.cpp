#include <iostream>
#include <cmath>
#include "Option08.h"
#include "BinomialTreeModel02.h"
#include "BinLattice02.h"

using namespace std;
namespace fre{
        
    Option::~Option(){}
    
    double Call::Payoff(double z) const
    {
        if(z>K) return z-K;
        return 0.0;
    }
    
    double Put::Payoff(double z) const
    {
        if (z<K) return K-z;
        return 0.0;
    }
    
    
    double OptionCalculation::PriceByCRR(const BinomialTreeModel& Model)
    {
        double q = Model.RiskNeutProb();
        int N = pOption -> GetN();
        vector<double> Price(N+1);
        
        for (int i=0; i<=N; i++){
            Price[i] = pOption -> Payoff(Model.CalculateAssetPrice(N,i));
        }
        for (int n=N-1; n>=0; n--){
            for (int i=0; i<=n; i++){
                Price[i] = (q*Price[i+1] + (1-q)*Price[i])/Model.GetR();
            }
        }
        
        double optionPrice = Price[0];
        return optionPrice;
    }
    
    
    double OptionCalculation::PriceByCRR(const BinomialTreeModel& Model, BinLattice<double>& PriceTree, BinLattice<double>&StockTree, BinLattice<double>& MoneyMarketTree)
    {
        double q = Model.RiskNeutProb();
        int N = pOption -> GetN();
        
        PriceTree.SetN(N);
        StockTree.SetN(N);
        MoneyMarketTree.SetN(N);
        
        double ContVal = 0;
        
        for (int i=0; i<=N; i++)
        {
            PriceTree.SetNode(N,i,pOption -> Payoff(Model.CalculateAssetPrice(N,i)));
        }
        
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0; i<=n; i++)
            {
                // ContVal = H(n,i)
                ContVal = (q*PriceTree.GetNode(n+1,i+1)+(1-q)*PriceTree.GetNode(n+1,i))/Model.GetR();
                PriceTree.SetNode(n,i,ContVal);
            }
        }
        
        
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0; i<=n; i++)
            {
                // x(n,i) = (H(n+1,i+1) - H(n+1,i)) / S(n+1,i+1) - S(n+1,i)
                double x = (PriceTree.GetNode(n+1,i+1) - PriceTree.GetNode(n+1, i)) / (Model.CalculateAssetPrice(n+1, i+1) - Model.CalculateAssetPrice(n+1, i));
                // y(n,i) = (H(n+1,i) - x(n,i)*S(n+1,i)) / R
                double y = (PriceTree.GetNode(n+1, i) - x*Model.CalculateAssetPrice(n+1, i)) / Model.GetR();
                
                StockTree.SetNode(n,i,x);
                MoneyMarketTree.SetNode(n,i,y);
            }
        }
        
        double optionPrice = PriceTree.GetNode(0,0);
        return optionPrice;
    }
    
    double OptionCalculation::PriceBySnell(const BinomialTreeModel& Model, BinLattice<double>& PriceTree, BinLattice<bool>& StoppingTree)
    {
        double q = Model.RiskNeutProb();
        int N = pOption -> GetN();
        
        PriceTree.SetN(N);
        StoppingTree.SetN(N);
        
        double ContVal = 0;
        
        for (int i=0; i<=N; i++)
        {
            PriceTree.SetNode(N,i,pOption->Payoff(Model.CalculateAssetPrice(N,i)));
            StoppingTree.SetNode(N,i,1);
        }
        
        for (int n=N-1; n>=0; n--){
            for (int i=0; i<=n; i++)
            {
                ContVal = (q*PriceTree.GetNode(n+1,i+1)+(1-q)*PriceTree.GetNode(n+1,i))/Model.GetR();
                PriceTree.SetNode(n,i,pOption->Payoff(Model.CalculateAssetPrice(n,i)));
                StoppingTree.SetNode(n,i,1);
                
                if (ContVal>PriceTree.GetNode(n,i))
                {
                    PriceTree.SetNode(n,i,ContVal);
                    StoppingTree.SetNode(n,i,0);
                }
                else if (PriceTree.GetNode(n,i) == 0.0)
                {
                    StoppingTree.SetNode(n,i,0);
                }
            }
        }
        
        double optionPrice = PriceTree.GetNode(0,0);
        return optionPrice;
    }
}