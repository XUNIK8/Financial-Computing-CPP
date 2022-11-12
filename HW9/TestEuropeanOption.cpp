// TestEuropeanOption.cpp
// Test program for the exact solutions of European options.
// (C) Datasim Component Technology BV 2003-2006
//

#include "EuropeanOption.hpp"
#include <iostream>

int main()
{
	const char* optType = NULL;
	
	// Q1: Call Price by default
	EuropeanOption callOption;
	optType = callOption.GetOptType();
	cout << "OptType:" << *optType << "\tCall option on a stock:" << callOption.Price() << endl;
	
	
	double U = 50.0;
	double K = 50.0;
	double T = 0.25;
	double r = 0.10;
	double sig = 0.30;
	char OptionType = 'P';
	
	// Q2: Put Price without dividend
	double q1 = 0.0;	

	EuropeanOption indexOption1(r, sig, K, T, U, q1, OptionType);
	optType = indexOption1.GetOptType();
	cout << "OptType:" << *optType << "\tPut option on a stock:" << indexOption1.Price() << endl;
	
	
    // Q3: Put Price with dividend
	double q2 = 0.119793;	

	EuropeanOption indexOption2(r, sig, K, T, U, q2, OptionType);
	optType = indexOption2.GetOptType();
	cout << "OptType:" << *optType << "\tPut option with dividend:" << indexOption2.Price() << endl;

	return 0;
}

/*
OptType:C       Call option on a stock:2.13293
OptType:P       Put option on a stock:2.37561
OptType:P       Put option with dividend:3.03039
*/