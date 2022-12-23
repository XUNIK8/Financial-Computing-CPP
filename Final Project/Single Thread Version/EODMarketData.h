#pragma once

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
#include <thread>
#include <vector>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;
typedef map<string, double> Stock_data;
typedef map<string, Stock_data> Popul_data;
typedef map<string,Matrix> Matrix_;

const int core_num = int(thread::hardware_concurrency());

struct EAInfo{
	string date;
	string period_ending;
	double estimate;
	double reported;
	double surprise;
	double surprise_percent;
};


class EODMarketData{
	private:
		unsigned N;
		const char* cIWB3000SymbolFile;
		const char* EAFile;
		const char* MarketCalendarFile;
		string default_start_date;
		
		vector<string> symbol_vector; // stock symbol frome EAFile
		vector<string> EA_date_vector; // EA_date from EAFile
		vector<string> market_calendar_vector; // US trading day
		
		map<string, string> start_date_map; // for every EA_date, calculate start date
		map<string, string> end_date_map; // for every EA_date, calculate end date
		map<string, EAInfo> ea_info_map; // key: stock, value: EAData of stock from EAFile;
		map<string, Stock_data> data_map; // key: stock, value: {date: price} of stock
		
	public:
		EODMarketData();
		void Reconstructor(void);
		
		void populate_ea_info_map(vector<string>& symbols, vector<string>& dates);
		void populate_market_calendar(vector<string>& dates);
		void populate_start_end_date(map<string, string>& start_date_map, map<string, string>& end_date_map);
		void populate_stock_data_map_from_web(vector<string> symbol_vector, map<string, Stock_data>& data_map);
		Stock_data download_stock_data_from_web(CURL* handle, string symbol, string date, string start_date, string end_date);
		
		int GetN(){return N;}
		vector<string> get_market_calendar_vector(){return market_calendar_vector;}
		map<string, EAInfo> get_ea_info_map(){return ea_info_map;}
		map<string, Stock_data> get_data_map(){return data_map;}
		~EODMarketData(){}
};