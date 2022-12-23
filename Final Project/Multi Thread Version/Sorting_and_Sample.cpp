#include "Sorting_and_Sample.h"
#include <string>


void SortingGroup::sort_group(){
    /*
    sort the stocks into 3 groups, pushed in 3 vectors
    */
    
    vector<double> vector_surprise_percent; // vector for surprise_percent
    string symbol;
    
    map<string, Stock_data> map_string = market_data.get_data_map();
    map<string, EAInfo> map_surprise = market_data.get_ea_info_map();
    for (map<string, Stock_data>::iterator itr = map_string.begin(); itr != map_string.end(); itr++){
        sorting_symbol.push_back(itr -> first);
        vector_surprise_percent.push_back(map_surprise[(itr -> first)].surprise_percent);
    }
    
    // for (vector<string>::iterator itr = sorting_symbol.begin(); itr != sorting_symbol.end(); itr++){
    //     vector_surprise_percent.push_back(map_surprise[(*itr)].surprise_percent);
    // }
    
    vector<double> sorting_surprise_percent = vector_surprise_percent; // copy vector for sorting surprise_percent
    
    // sorting according to surprise value
    sort(sorting_surprise_percent.begin(), sorting_surprise_percent.end());
    
    // Get thresholds
    int third = sorting_surprise_percent.size()/3;
    double threshold1 = sorting_surprise_percent[third]; // get group threshold1
    double threshold2 = sorting_surprise_percent[third*2]; // get group threshold2 which is greater than 1
    
    for (unsigned int i = 0; i < vector_surprise_percent.size(); i++){ // sorting the stocks into 3 groups and fill the symbol map
        symbol = sorting_symbol[i]; 
        double surp = vector_surprise_percent[i];
        if (surp < threshold1)
            {miss.push_back(symbol);symbol_group[symbol] = "miss";}
            else if (surp > threshold2)
            {beat.push_back(symbol);symbol_group[symbol] = "beat";}
            else
            {meet.push_back(symbol);symbol_group[symbol] = "meet";}
    }
 }


vector<string> Sample::get_sample(int i){
    /*
    int i: random number seed
    the output is the sampling result which is a vector
    */
    unsigned int M = 80;
    int N = population.size(); // sample 80 from population[0,N-1]
    vector<string> sample;
    set<int> s; // we use set to make sure all the numbers are different
    
    srand(i);
    while( s.size() < M )
    {
       int random_value = (rand() % (N)); // get random value [0,N-1]
       s.insert(random_value);
    }
    
    for (std::set<int>::iterator it=s.begin(); it!=s.end(); it++)
        sample.push_back(population[*it]); // push back the sampling result
    
    return sample;
}
