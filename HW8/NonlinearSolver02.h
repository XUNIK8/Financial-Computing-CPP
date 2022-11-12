#pragma once
#include "Bond.h"

namespace fre{
    class NonlinearSolver
    {
        private:
            double Tgt;
            double LEnd;
            double REnd;
            double Acc;
            double Guess;
            
        public:
            NonlinearSolver():Tgt(0), LEnd(0), REnd(0), Acc(0), Guess(0){}
            NonlinearSolver(double Tgt_, double LEnd_, double REnd_, double Acc_, double Guess_):Tgt(Tgt_), LEnd(LEnd_), REnd(REnd_), Acc(Acc_), Guess(Guess_){}
            ~NonlinearSolver(){}
            
            void UpdateSolver(double Tgt_, double LEnd_, double REnd_, double Acc_, double Guess_)
            {
                Tgt = Tgt_;
                LEnd = LEnd_;
                REnd = REnd_;
                Acc = Acc_;
                Guess = Guess_;
            }
            
            double SolveByBisect(Bond* Bond);
            double SolveByNR(Bond* Bond);
    };
}