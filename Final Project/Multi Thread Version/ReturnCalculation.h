#include "curl/curl.h"
#include "Sorting_and_Sample.h"
#include "EODMarketData.h"
#include <iostream>
#include <map>
#include <string> 
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;


class ReturnCalculation : public SortingGroup
{
    private:
        Stock_data IWVReturn;
        Popul_data stockdata = market_data.get_data_map();
        unsigned int N = market_data.GetN();
        Matrix_ Final_Marix;
        
    
    public:
        ReturnCalculation(){};
        
        Popul_data GetStockdata(){return stockdata;}
        Stock_data IWVReturnCal(); // get IWV return
        Popul_data StockreturnCal(vector<string> symbolvector_); // get stock return
        
        Matrix ARCal(Popul_data Stockreturn_, Stock_data IWVReturn_); //Calculate Abnormal Return
        Vector AARCal(Matrix AR_); //Calculate Average Abnormal Return
        Vector CAARCal(Vector AAR_); //Calculate Cumulative Average Abnormal Return
        Popul_data CRCal(); // cumulative stock return
        void AveCal(vector<string> beat_group_, vector<string> meet_group_, vector<string> miss_group_); //Calculate Average AAR, CAAR, AAR_STD, CAAR_STD and fill them into Final_marix
        
        void filling_final_matrix(string groupname, vector<string> group_); //Repeate function AveCal 3 times(with different group) to get Final_marix(a map) with group names as keys and matrices as values(Each matrix contains four vectors, respectively AAAR, AAR_STD, ACAAR, CAAR_STD.)
        Matrix_ GetMatrix_(){return Final_Marix;} //Get Final_Marix
        unsigned int GetN() {return N;} //Get number of N
        ~ReturnCalculation(){}
};
