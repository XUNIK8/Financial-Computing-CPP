#include "ReturnCalculation.h"
using namespace std;

// Operators overloading session
Vector operator+(const Vector& V, const Vector& W)
{
    int d = (int)V.size();
    Vector U(d);
    
    for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
    
    return U;
}
    
    
Vector operator*(const double& a, const Vector& V)
{
    int d = (int)V.size();
    Vector U(d);
    
    for (int j = 0; j < d; j++) U[j] = a * V[j];
    
    return U;
}


Vector operator*(const Vector& V, const Vector& W)
{
    int d = (int)V.size();
    Vector U(d);
    
    for (int j = 0; j < d; j++) U[j] = V[j] * W[j];
    
    return U;
}

Vector operator^(const Vector& C, const double& a)
{
    int m = (int)C.size();
    Vector W(m);
    
    for (int i = 0; i < m; i++)
    {
        W[i] = pow(C[i], a);
    }
    
    return W;
}


// Calculation session
Stock_data ReturnCalculation::IWVReturnCal()
{
/*
curr -> second points to the current stock price which will be replaced with stock return. 
cur starts with the second location.
prev -> second points to the price of the previous day. 
erase the frist day from the dataset

*/
    Stock_data IWVReturn = stockdata["IWV"];
    Stock_data IWVReturn_copy = IWVReturn;
    Stock_data :: iterator prev = IWVReturn_copy.begin();
    Stock_data :: iterator curr = std::next(IWVReturn.begin(), 1);
    
    for (; curr != IWVReturn.end(); curr ++)
    {
        curr->second = (curr->second / prev->second) - 1;
        prev ++;
    } // IWV return
    
    IWVReturn.erase(IWVReturn.begin());
    
    return IWVReturn;
};


Popul_data ReturnCalculation::StockreturnCal(vector<string> symbolvector_)
{
/*
The first iteration gives us the price data for each stock.
The second iteration is used to calculate every stock’s returns
for every stock, d is the data of the prices
similar methodology with IWVReturnCal
*/
    Popul_data Stockreturn;
    vector<string>::iterator itor;
    
    for (itor = symbolvector_.begin(); itor != symbolvector_.end();)
    {
        if (*itor == "IWV") 
        {
            itor = symbolvector_.erase(itor);
        }
        else
        {
            itor++;
        }
    } // remove IWV from the data
    
    vector<string>::iterator itr;
    for (itr = symbolvector_.begin(); itr != symbolvector_.end(); itr ++)
    {   
        Stock_data d = stockdata[*itr]; // *itr1: symbol
        Stock_data d_copy = d;
        Stock_data :: iterator prev = d_copy.begin();
        Stock_data :: iterator curr = std::next(d.begin(), 1);
        
        for (; curr != d.end(); curr ++)
        {
            curr->second = curr->second / prev->second - 1;
            prev ++;
        }
        
        d.erase(d.begin());
        Stockreturn[*itr] = d; // stock return
    }
    
    return Stockreturn;
}


Matrix ReturnCalculation :: ARCal(Popul_data Stockreturn_, Stock_data IWVReturn_)
{
/*
1. Matching the trading days
2. Subtracting (using formula)
3. Converting map into matrix
the first if function help us to exit the iteration once all the stock trading days have been matched with IWV trading days
*/
    map<string,Stock_data> :: iterator itr1;
    map<string,Vector> return_map;
    for (itr1 = Stockreturn_.begin(); itr1 != Stockreturn_.end(); itr1++)
    {
        Vector a;
        Stock_data :: iterator itr2;
        Stock_data d = Stockreturn_[itr1->first];
        Stock_data :: iterator itr3 = d.begin();
        
        for (itr2 = IWVReturn_.begin(); itr2 != IWVReturn_.end(); itr2++)
        {
            if (a.size() == 2 * N)
            {
                break;
            }
            else if (itr2->first == itr3->first)
            {
                double return_day = itr3->second-itr2->second;
                a.push_back(return_day);
                itr3++;
            }
        }
        return_map[itr1->first] = a;
    }
    
    Matrix AbnormalReturn(return_map.size());
    map<string, Vector> :: iterator itor;
    int ii;
    for (itor = return_map.begin(), ii = 0; itor != return_map.end(); itor++, ii++)
    {
        AbnormalReturn[ii].resize(2 * N);
        AbnormalReturn[ii] = itor->second;
    }
    
    return AbnormalReturn;
}


Vector ReturnCalculation::AARCal(Matrix AR_)
{
    /*
    Calculate Average abnormal return;
    param AR_: Matrix of abnormal return of stocks;
    return 100 * AAR: AAR is the vector of average abonrmal return, multiply it by 100 to make its elements percentage numbers;
    */
    int d = 2 * N;
    Vector AAR;
    AAR.resize(d);
    
    for (int i = 0; i < d; i++) AAR[i] = 0.0;
    
    for (unsigned int i = 0; i < AR_.size(); i++)
    {
        AAR = (1.0 / (i + 1.0)) * (i * AAR + AR_[i]);
    }
    
    return 100 * AAR;
}


Vector ReturnCalculation::CAARCal(Vector AAR_)
{       
    /*
    Calculate Cumulative Average abnormal return;
    param AAR_: Vector of Average abnormal return;
    return CAAR: CAAR is the vector of Cumulative Average abnormal return;
    */
    int d = AAR_.size();
    Vector CAAR;
    CAAR.resize(d);
    
    for (int i = 0; i < d; i++) CAAR[i] = 0.0;
    
    double COUNT = 0;
    for (int j = 0; j < d; j++)
    {
        COUNT = COUNT + AAR_[j];
        CAAR[j] = COUNT;
    }
    
    return CAAR;
}


void ReturnCalculation::AveCal(vector<string> beat_group_, vector<string> meet_group_, vector<string> miss_group_)
{
    /*
    Filling final matrix(a map) with group names as keys and matrices as values(Each matrix contains four vectors, respectively AAAR, AAR_STD, ACAAR, CAAR_STD.)
    param vector<string> beat_group_: A vector contains names of 80 sample stocks of a group.
    */
    filling_final_matrix("Beat_group", beat_group_);
    filling_final_matrix("Meet_group", meet_group_);
    filling_final_matrix("Miss_group", miss_group_);
}


void ReturnCalculation::filling_final_matrix(string groupname, vector<string> group_)
{
    /*
    Repeate sampling for 40 times. Calculate average AAR, CAAR, AAR_STD, CAAR_STD of 40 repetition and fill them into Final_Marix.
    param groupname: The name of the group, used as key in the Final_marix.
    param vector<string> group_: A vector contains names of 80 sample stocks of a group.
    */
    int d = 2 * N;
    Stock_data IWVReturn = IWVReturnCal();
    
    Vector AAAR_group;
    AAAR_group.resize(d);
    Vector ACAAR_group;
    ACAAR_group.resize(d);
    Sample sample_(group_);
    Vector AAR_group_sq;
    AAR_group_sq.resize(d);
    Vector CAAR_group_sq;
    CAAR_group_sq.resize(d);
    Vector AAR_std_group;
    AAR_std_group.resize(d);
    Vector CAAR_std_group;
    CAAR_std_group.resize(d); 
    
    for (int m = 0; m < 40; m++)
    {
        vector<string> sample = sample_.get_sample(m);
        Popul_data Stockreturn = StockreturnCal(sample);
        Matrix AR = ARCal(Stockreturn, IWVReturn);
        Vector AAR = AARCal(AR);
        Vector CAAR = CAARCal(AAR);
        AAAR_group = (1.0/(m+1.0)) * (m * AAAR_group + AAR);
        ACAAR_group = (1.0/(m+1.0)) * (m * ACAAR_group + CAAR);
        AAR_group_sq = (1.0/(m+1.0)) * (m * AAR_group_sq + AAR * AAR);
        CAAR_group_sq = (1.0/(m+1.0)) * (m * CAAR_group_sq + CAAR * CAAR);
    }
    
    AAR_std_group = (AAR_group_sq + (-1.0) * AAAR_group * AAAR_group) ^ 0.5;
    CAAR_std_group = (CAAR_group_sq + (-1.0) * ACAAR_group * ACAAR_group) ^ 0.5;
    Matrix Matrix_group;
    Matrix_group.resize(4);
    
    for(int i=0;i<4;i++) Matrix_group[i].resize(2*N);
    
    Matrix_group[0] = AAAR_group;
    Matrix_group[1] = AAR_std_group;
    Matrix_group[2] = ACAAR_group;
    Matrix_group[3] = CAAR_std_group;
    Final_Marix[groupname] = Matrix_group;
}


Popul_data ReturnCalculation::CRCal()
{
    /*
    The first iteration gives us the price data for each stock.
    The second iteration is used to calculate every stock’s returns
    Use variable count to keep track of the cumulative return
    */
    Popul_data CR = StockreturnCal(sorting_symbol);
    Popul_data :: iterator itr1 = CR.begin();
    
    for (; itr1 != CR.end(); itr1 ++)
    {
        Stock_data tem = itr1->second;
        double count = 0.0;
        Stock_data :: iterator itr2 = tem.begin();
        
        for (; itr2 != tem.end(); itr2 ++)
        {
            count = count + 100*itr2->second;    
            itr2->second = count;
        }
        
        CR[itr1->first] = tem;
    }
    return CR; // Cumulative Stock Return
}