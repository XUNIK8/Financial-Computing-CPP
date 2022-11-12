#include "NonlinearSolver02.h"

namespace fre{
    double NonlinearSolver::SolveByBisect(Bond* Bond)
    {
        double left = LEnd, right = REnd, mid = (left + right)/2;
        double y_left = Bond->Value(left) - Tgt, y_mid = Bond->Value(mid) - Tgt;
        
        while (mid - left>Acc)
        {
            if ((y_left > 0 && y_mid > 0) || (y_left < 0 && y_mid < 0))
            {
                left = mid, y_left = y_mid;
            }
            else right = mid;
            
            mid = (right + left)/2; 
            y_mid = Bond->Value(mid) - Tgt;
        }
        return mid;
    }

    double NonlinearSolver::SolveByNR(Bond* Bond)
    {
        double x_prev = Guess;
        double x_next = x_prev - (Bond->Value(x_prev)-Tgt) / Bond->Derive(x_prev);
        
        while (x_next - x_prev > Acc || x_prev - x_next > Acc)
        {
            x_prev = x_next;
            x_next = x_prev - (Bond->Value(x_prev)-Tgt) / Bond->Derive(x_prev);
        }
        return x_next;
    }
    
}