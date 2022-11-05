#pragma once

#include "BinomialTreeModel02.h"
#include "BinLattice02.h"

namespace fre{
    class Option
    {
        private:
            Option(): N(0){}
            Option(const Option& option):N(option.N){}
        protected:
            int N;
        public:
            Option(int N_): N(N_){}
            int GetN() const {return N;}
            virtual double Payoff(double z) const = 0;
            virtual ~Option() = 0;
    };
    
    class Call : public Option
    {
        private:
            double K;
        public:
            Call(int N_, double K_): Option(N_),K(K_){}
            ~Call(){}
            double Payoff(double z) const;
    };
    
    class Put: public Option{
        private:
            double K;
        public:
            Put(int N_, double K_): Option(N_),K(K_){}
            ~Put(){}
            double Payoff(double z) const;
    };

    
    class OptionCalculation
    {
        private:
            Option* pOption;
            OptionCalculation(): pOption(0){}
            OptionCalculation(const OptionCalculation& optionCalculation) : pOption(optionCalculation.pOption){}
        public:
            OptionCalculation(Option*pOption_):pOption(pOption_){}
            ~OptionCalculation(){}
            double PriceByCRR(const BinomialTreeModel& model);
            double PriceByCRR(const BinomialTreeModel& model, BinLattice<double>& PriceTree, BinLattice<double>&StockTree, BinLattice<double>& MoneyMarketTree);
            double PriceBySnell(const BinomialTreeModel& model,BinLattice<double>& PriceTree,BinLattice<bool>& StoppingTree);
    };
}