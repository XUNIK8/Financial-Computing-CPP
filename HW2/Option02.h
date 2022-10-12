#pragma once

namespace fre {
	//pricing European option
	double PriceByCRR(double S0, double U, double D, double R, unsigned int N, double K, double(*payoff)(double z, double K));

	//computing call payoff
	double CallPayoff(double z, double K);
	
	double PutPayoff(double z, double K);
	
	double DigitCallPayoff(double z, double K);
	
	double DigitPutPayoff(double z, double K);
}