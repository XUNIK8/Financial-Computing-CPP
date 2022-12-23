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
#include "ReturnCalculation.h"
#include "gnuplot.h"

using namespace std;


int main() 
{
    cout << "--------------------------------INITIALIZATION--------------------------------" << endl << endl;
    cout << "[Initialize the number N (>=60)]" << endl << endl;
    
    ReturnCalculation *RC_ptr = new ReturnCalculation();
    RC_ptr->sort_group();
    
    int N = RC_ptr->GetN();
    
    vector<string> beat_group;
    vector<string> meet_group;
    vector<string> miss_group;
    
    beat_group = RC_ptr->get_beat();
    meet_group = RC_ptr->get_meet();
    miss_group = RC_ptr->get_miss();
    
    RC_ptr->AveCal(beat_group, meet_group, miss_group);


    // Menu session
    bool running = true; 
    string soption;
    string sgroup;
    string ticker;
    
    while (running) {
        cout << endl;   
        cout << "-------------------------------------MENU-------------------------------------" << endl << endl;
        cout << "1. Reset the number N" << endl;
        cout << "2. Pull info of a single stock" << endl;
        cout << "3. Show AAR, AAR-STD, CAAR and CAAR-STD for one group" << endl;
        cout << "4. Show the gnuplot graph with CAAR for all 3 groups" << endl;
        cout << "5. Exit" << endl << endl;
        cout << "Please Enter Number 1-5: ";
        cin >> soption;
        getchar();
        cout << endl;
        cout << "-----------------------------------FUNCTION-----------------------------------" << endl << endl;

        while ((soption.at(0) > '5' || soption.at(0) <= '0')) {
            cout << "------------------------------------REMINDER----------------------------------" << endl << endl;
            cout << "Invalid option. Please input a number from 1 to 5" << endl;
            cout << "1. Reset the number N" << endl;
            cout << "2. Pull info of a single stock" << endl;
            cout << "3. Show AAR, AAR-STD, CAAR and CAAR-STD for one group" << endl;
            cout << "4. Show the gnuplot graph with CAAR for all 3 groups" << endl;
            cout << "5. Exit" << endl << endl;
            cout << "Please Enter Number 1-5: ";
            cin >> soption;
            getchar();
            cout << endl;
            cout << "-----------------------------------FUNCTION-----------------------------------" << endl << endl;
        }


        int option = stoi(soption);
        switch (option) {
            
            case 1:{
                cout << "[Reset the number N]" << endl << endl;
                delete RC_ptr;
                RC_ptr = new ReturnCalculation();
                
                N = RC_ptr->GetN();
                
                RC_ptr->sort_group();
                beat_group = RC_ptr->get_beat();
                meet_group = RC_ptr->get_meet();
                miss_group = RC_ptr->get_miss();
                RC_ptr->AveCal(beat_group, meet_group, miss_group);
                
                break;
            }

            case 2: {
                cout << "[Pull info of one stock]" << endl << endl;
                cout << "Please enter stock ticker (print '0' to get back):";
                cin >> ticker;
                getchar();
                cout << endl;
                
                // Get back to the main menu
                if (ticker.at(0) == '0') break;
                
                // 1. Stock dates and daily prices (121)
                Stock_data info_map = RC_ptr->GetStockdata()[ticker];
                
                cout << "1. " << ticker << " - " << "2N+1 Dates and respective prices are: " << endl << endl;
                cout << left << setw(14) << "Dates"
                    << setw(12) << "Prices"
                    << endl;
                    
                for (Stock_data::iterator itr=info_map.begin();itr != info_map.end();itr++) {
                    cout << left << setw(14) << itr->first
                        << setw(12) << itr->second
                        << endl << endl;
                }

                // 2. Cumulative return
                Sample symbol_group;
                map<string,string> group_map = RC_ptr->get_symbol_group();
        
                Popul_data stock_cum_return = RC_ptr->CRCal();
                Stock_data target_stock_cum_return = stock_cum_return[ticker];
                
                cout << "2. " << ticker << " - " << "2N+1 days' cumulative returns are: " << endl << endl;
                cout << left << setw(14) << "Dates"
                    << setw(12) << "Cum Returns" 
                    << endl << endl;
                    
                Stock_data::iterator itr=target_stock_cum_return.begin();    
                for (int i = 0; i < 2*N; i++) {
                    cout << left << setw(14) << itr->first
                        << setw(12) << itr->second
                        << endl << endl;
                    itr++;
                }

                // 3. Group name
                cout << "3. " << ticker << " - " << "Group Name is: " << group_map[ticker] << endl << endl;
                
                // 4. Other Info
                // EODMarketData market_data = RC_ptr->get_market_data();
                EAInfo ea_info_struct = RC_ptr->get_market_data().get_ea_info_map()[ticker];
                
                cout << "4. " << ticker << " - " << "Other related information: " << endl;
                cout << "- Earning Announcement Date: " << ea_info_struct.date << endl;
                cout << "- Period Ending: " << ea_info_struct.period_ending << endl;
                cout << "- Estimated: " << ea_info_struct.estimate << endl;
                cout << "- Reported Earnings: " << ea_info_struct.reported << endl;
                cout << "- Surprise: " << ea_info_struct.surprise << endl;
                cout << "- Surprise %: " << ea_info_struct.surprise_percent << endl;
                cout << endl;
                
                break;
            }

            case 3: {
                cout << "[Show AAR, AAR-STD, CAAR and CAAR-STD for one group]" << endl << endl;
                cout << "Please enter the group selection (print '0' to get back): " << endl
                    << "1. Beat group" << endl
                    << "2. Meet group" << endl
                    << "3. Miss group" << endl
                    << endl;
                    
                cout << "Please Enter Number 1-3: ";
                cin >> sgroup;
                getchar();
                cout << endl;
                
                if (sgroup.at(0) == '0') break;

                while ((sgroup.at(0) > '3' || sgroup.at(0) <= '0')) {
                    cout << "Input a Number from 1 to 5 only" << endl << endl;
                    cout << "Please enter the group selection: " << endl
                        << "1. Beat group" << endl
                        << "2. Meet group" << endl
                        << "3. Miss group" << endl
                        << endl;
                    cout << "Please Enter Number 1-3: ";
                    cin >> sgroup;
                    getchar();
                    cout << endl;
                }
                
                
                Matrix_ metrics_matrix = RC_ptr->GetMatrix_();
                Vector AAR, AAR_STD, CAAR, CAAR_STD;
                
                int groupnum = stoi(sgroup);
                string groupname;
                
                if (groupnum == 1) { groupname = "Beat_group"; }
                else if(groupnum == 2) { groupname = "Meet_group"; }
                else { groupname = "Miss_group"; }
                
                cout << "Detailed Information for " << groupname << ":" << endl << endl;
                cout << left << setw(10) << "Dates"
                    << setw(12) << "AAR"
                    << setw(12) << "AAR STD"
                    << setw(12) << "CAAR"
                    << setw(12) << "CAAR STD"
                    << endl << endl;
                    
                for (int i = 0; i < 2*N; i++) {
                    cout << left << setw(10) << i-int(N)+1
                        << setw(12) << metrics_matrix[groupname][0][i] 
                        << setw(12) << metrics_matrix[groupname][1][i]
                        << setw(12) << metrics_matrix[groupname][2][i]
                        << setw(12) << metrics_matrix[groupname][3][i]
                        << endl << endl;
                }
                
                break; 
            }

            case 4: {
                cout << "[Show the gnuplot graph with CAAR for all 3 groups]" << endl << endl;
                Matrix_ metrics_matrix = RC_ptr->GetMatrix_();
                Vector beat_ACAAR, meet_ACAAR, miss_ACAAR;
                beat_ACAAR = metrics_matrix["Beat_group"][2];
                meet_ACAAR = metrics_matrix["Meet_group"][2];
                miss_ACAAR = metrics_matrix["Miss_group"][2];

                gnuplot CAAR_plot(beat_ACAAR, meet_ACAAR, miss_ACAAR);
                CAAR_plot.plotResults();
                    
                break; 
            }

            case 5: {
                running = false;
                cout << "[Program Exited]" << endl << endl;
                delete RC_ptr;
                RC_ptr = NULL;
                
                break;
            }
            
            return 0;
        };                 
    };
    
    return 0;
}
