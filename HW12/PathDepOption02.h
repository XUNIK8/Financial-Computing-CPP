#pragma once
#include "Matrix.h"
#include "MCModel02.h"

namespace fre {
    class PathDepOption
    {
    protected:
        double Price;
        Vector delta;
        double T;
        double K;
        int m;
    public:
        PathDepOption(double T_, double K_, int m_) : Price(0.0), T(T_), K(K_), m(m_) {}
        double PriceByMC(MCModel& Model, long N, double episilon);
        virtual ~PathDepOption() {}
        virtual double Payoff(const SamplePath& S) const = 0;
        double GetPrice(){return Price;}
        Vector GetDelta(){return delta;}
    };

    class ArthmAsianCall : public PathDepOption
    {
    public:
        ArthmAsianCall(double T_, double K_, int m_) : PathDepOption(T_, K_, m_) {}
        double Payoff(const SamplePath& S) const;
        
    };
}

