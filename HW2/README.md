# HW2 Instruction

Homework 2 assignment (copied from Topic 2 lecture slide # 46):

Include the ability to price digital calls and puts in the program developed in the present section by adding new payoff functions to the files Option02.h, Option02.cpp and OptionPrice02.cpp

**double DigitCallPayoff(double z, double K)**

{

   if (z>K) return 1.0;

   return 0.0;

}

**double DigitPutPayoff(double z, double K)**

{

   if (z<K) return 1.0;

   return 0.0;

}

**The following is the sample input and output you should use to verify your program:**

/*

Enter S0: 106
Enter U:  1.15125
Enter D:  0.86862
Enter R:  1.00545

Input data checked
There is no arbitrage

Enter call option data:
Enter steps to expiry N: 8
Enter strike price K:    100

European Call option price = 21.68
European Put option price = 11.43
Digit Call option price = 0.58
Digit Put option price = 0.38

*/
