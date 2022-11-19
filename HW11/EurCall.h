#pragma once
namespace fre {
    class EurCall
    {
    private:
        double T, K;
        double d_plus(double S0, double sigma, double r);
        double d_minus(double S0, double sigma, double r);
    public:
        EurCall(double T_, double K_) : T(T_), K(K_) {}
        double PriceByBSFormula(double S0, double sigma, double r);
        double VegaByBSFormula(double S0, double sigma, double r);
        double DeltaByBSFormula(double S0, double sigma, double r);
    };
}


