#pragma once

#include <vector>

using namespace std;

class gnuplot{
    private:
        vector<double> yData1;
        vector<double> yData2;
        vector<double> yData3;
        int dataSize;
        
    public:
        gnuplot(const vector<double> &yData1_, const vector<double> &yData2_, const vector<double> &yData3_)
        {
            yData1 = yData1_;
            yData2 = yData2_;
            yData3 = yData3_;
            dataSize = yData1_.size();
        }
        ~gnuplot(){}
        vector<double> GetData1(){return yData1;}
        vector<double> GetData2(){return yData2;}
        vector<double> GetData3(){return yData3;}
        void plotResults() const;
};