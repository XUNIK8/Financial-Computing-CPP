#include <iostream>

using namespace std;

class DefInt{
    private:
        double a,b;
        double (*pf)(double);
        
    public:
        // Constructor: with parameters
        DefInt(double inf, double sup, double (*f)(double)):a(inf), b(sup), pf(f) {}
        // {
        //     a = inf;
        //     b = sup;
        //     pf = f;
        // }
        
        // By Trapzoid
        double ByTrapzoid(int N)
        {
            double sum = 0;
            double h = (b-a)/N;
            double area;
            
            for (int k = 1; k <= N; k++)
            {
                sum += pf(a+(k-1)*h) + pf(a+k*h);
            }
            
            area = h/2 * sum;
            return area;
        }
        
        // By Simpson
        double BySimpson()
        {
            double area;
            
            area = (b-a)/6 * (pf(a) + pf(b) + 4*pf((a+b)/2));
            return area;
        }
};


// f(x) function
double fx(double x)
{
    return x*x*x - x*x + 1;
}

int main()
{
    double inf = 1.0;
    double sup = 2.0;
    int N = 100;

    DefInt MyInt(inf, sup, fx);
    cout << "Approximation By Trapzoid = " << MyInt.ByTrapzoid(N) << endl;
    cout << "Approximation By Simpson = " << MyInt.BySimpson() << endl;
    return 0;
}


/* 
Result:

if N = 100:
Approximation By Trapzoid = 2.41673
Approximation By Simpson = 2.41667

if N = 1000:
Approximation By Trapzoid = 2.41667
Approximation By Simpson = 2.41667
*/