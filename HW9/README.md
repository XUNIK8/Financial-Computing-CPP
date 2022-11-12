# Homework_Assignment_9

The header file and cpp files in this homework assignment are from the Daniel Duffy's book, Introduction to C++ for Financial Engineers, for calculating European options with BS formula. Please complete following 3 tasks with the provided header file and cpp files:

Question 1: 

Move data into private section
Remove init() and copy() functions. Implement them directly in constructors.
Use char point and dynamic allocation to replace the STL string, optType. Make sure no memory leak
Make function n() and N() as private functions
Create a member function GetOptType() to get the optType in main() function. Do not hard-coded option type in cout.

Question 2:

Calculate the price of a three-month European put option on a non-dividend-paying stock with a strike price of $50 when the current stock price is $50, the risk-free interest rate is 10% per annum, and the volatility is 30% per annum.


Question 3:

What difference does it make to your calculations in Question 2 if a dividend of $1.50 is expected in two months? 

Expand TestEuropeanOption.cpp for question 2 and 3.

Hint: Question 2 and 3 are from John Hull's Options, Futures, and Other Derivatives. You could check John Hull's book for the way to solve the questions and implement them using Daniel Duffy's codes.

The following is expected result for Question 1, 2 and 3:

Q1: Call option on a stock: 2.13293

Q2: Put option on a stock: 2.37561

Q3: Put option with dividend: 3.03039
