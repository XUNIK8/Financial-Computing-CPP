#pragma once
#include "MCModel.h"
namespace fre {
    class PathDepOption
    {
    protected:
        double Price, PricingError, delta;
        int m;
        double K, T;
    public:
        PathDepOption(double T_, double K_, int m_) :Price(0.0), PricingError(0.0), delta(0.0), m(m_), K(K_), T(T_)
        {}
        virtual ~PathDepOption() {}
        virtual double Payoff(const SamplePath& S) const = 0;
        double PriceByMC(const MCModel& Model, long N, double epsilon);
        double PriceByVarRedMC(const MCModel& Model, long N, PathDepOption& CVOption, double epsilon);
        virtual double PriceByBSFormula(const MCModel& Model) { return 0.0; }
        double GetPrice() { return Price; }
        double GetPricingError() { return PricingError; }
        double GetDelta() { return delta; }
    };


    class DifferenceOfOptions : public PathDepOption
    {
    private:
        PathDepOption* Ptr1;
        PathDepOption* Ptr2;
    public:
        DifferenceOfOptions(double T_, double K_, int m_, PathDepOption* Ptr1_, PathDepOption* Ptr2_) : PathDepOption(T_, K_, m_), Ptr1(Ptr1_), Ptr2(Ptr2_)
        { }
        double Payoff(const SamplePath& S) const
        {
            return Ptr1->Payoff(S) - Ptr2->Payoff(S);
        }
    };

    class ArthmAsianCall : public PathDepOption
    {
    public:
        ArthmAsianCall(double T_, double K_, int m_) : PathDepOption(T_, K_, m_) {}
        double Payoff(const SamplePath& S) const;
    };

}





