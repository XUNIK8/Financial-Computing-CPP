#include "curl/curl.h"
#include <cstring>
#include <fstream>
#include <locale>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>  
#include <stdio.h>
#include <string> 
#include <vector>
#include <algorithm>
#include "EODMarketData.h"

using namespace std;


class SortingGroup{
    private:
        vector<string> beat; // beat group
        vector<string> miss; // miss group
        vector<string> meet; // meet group
        map<string,string> symbol_group; // key -> symbol; value -> group
    
    protected:
        EODMarketData market_data; // EOD class object
        vector<string> sorting_symbol;
    
    public:
        SortingGroup(){};
        void sort_group(); // function of how to sort the three groups
        vector<string> get_beat(){return beat;}
        vector<string> get_miss(){return miss;}
        vector<string> get_meet(){return meet;}
        map<string,string> get_symbol_group(){return symbol_group;} // key -> symbol; value -> group
        EODMarketData get_market_data(){return market_data;}
        virtual ~SortingGroup(){};
};


class Sample{
    private:
        vector<string> population; // population: beat_group; meet_group; miss_group
    
    public:
        Sample(){}
        Sample(vector<string> const &population_):population(population_){}
        vector<string> get_sample(int i);// get samples; i:random number seed
        void SetPopulation(const vector<string> &population_){population = population_;}
        ~Sample(){}
};