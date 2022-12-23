#include "EODMarketData.h"

struct MemoryStruct {
	char* memory;
	size_t size;
};


void* myrealloc(void* ptr, size_t size)
{
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}


int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}


int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)data;
	mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}


////////////////////////////////////////////////////////////////////////////////////


EODMarketData::EODMarketData()
{
// enter N to retrieve data
// download stock price data from website and store them in data_map
// read csv EAFile and store them in ea_info_map
	cout<<"Please enter N to retrieve 2N+1 days of historical price data for all stocks."<<endl;
	cin>>N;
	while (N<60)
	{
		cout<<"N should not be less than 60, Please enter again."<<endl;
		cin>>N;
	}
	
	cIWB3000SymbolFile = "Russell_3000_component_stocks.csv";
	EAFile = "Russell3000EarningsAnnouncements.csv";
	MarketCalendarFile = "market_calendar.csv";
	default_start_date = "2020-01-01";
	
	populate_ea_info_map(symbol_vector, EA_date_vector);
	populate_market_calendar(market_calendar_vector);
	populate_start_end_date(start_date_map, end_date_map);
	populate_stock_data_map_from_web(symbol_vector, data_map);
}


void EODMarketData::populate_ea_info_map(vector<string>& symbols, vector<string>& dates)
{
// read EAFile and change the format of dates
// symbols: store stock symbol in this vector 
// dates: store EA date in this vector
    map<string, string> month_map;
    month_map["JAN"]="01";
    month_map["FEB"]="02";
    month_map["MAR"]="03";
    month_map["APR"]="04";
    month_map["MAY"]="05";
    month_map["JUN"]="06";
    month_map["JUL"]="07";
    month_map["AUG"]="08";
    month_map["SEP"]="09";
    month_map["OCT"]="10";
    month_map["NOV"]="11";
    month_map["DEC"]="12";
    
	ifstream fin;
	fin.open(EAFile, ios::in);
	string line, raw_date, date, symbol, period_ending;
	double estimate, reported, surprise, surprise_percent;
	getline(fin, line); // skip the first line
	//get stock symbol, EA date, surprise%
	while (getline(fin, line))
	{
		symbol = line.substr(0, line.find_first_of(','));
        line.erase(0, line.find_first_of(',')+1);
        
        raw_date = line.substr(0, line.find_first_of(','));
        date = "20"+raw_date.substr(7)+"-"+month_map[raw_date.substr(3,3)]+"-"+raw_date.substr(0,2);
        line.erase(0, line.find_first_of(',')+1);
        
        period_ending = line.substr(0, line.find_first_of(','));
        line.erase(0, line.find_first_of(',')+1);
        
        estimate = strtod(line.substr(0, line.find_first_of(',') + 1).c_str(), NULL);
        line.erase(0, line.find_first_of(',')+1);
        
        reported = strtod(line.substr(0, line.find_first_of(',') + 1).c_str(), NULL);
        line.erase(0, line.find_first_of(',')+1);
        
        surprise = strtod(line.substr(0, line.find_first_of(',') + 1).c_str(), NULL);
        line.erase(0, line.find_first_of(',')+1);
        
        surprise_percent = strtod(line.c_str(), NULL);
        
        EAInfo ea_info = {date, period_ending, estimate, reported, surprise, surprise_percent};
        ea_info_map[symbol] = ea_info;
        // cout<<symbol<<" "<<date<<" "<<period_ending<<" "<<estimate<<" "<<reported<<" "<<surprise<<" "<<surprise_percent<<endl;
        
		symbols.push_back(symbol);
		dates.push_back(date);
	}
	fin.close();
}


void EODMarketData::populate_market_calendar(vector<string>& dates)
{
// read trading dates 
// dates: store trading dates in this vector
	ifstream fin;
	fin.open(MarketCalendarFile, ios::in);
	string date;
	while (getline(fin, date)) {
		dates.push_back(date.substr(0,10));
	}
	fin.close();
}


void EODMarketData::populate_start_end_date(map<string, string>& start_date_map, map<string, string>& end_date_map)
{
// for every EA date, calculate the start and end date to download data using url
// start_date_map, end_date_map: key: EA date, value: start and end date
	set<string> st(EA_date_vector.begin(), EA_date_vector.end());
	set<string>::iterator itr = st.begin();
	for(; itr!=st.end(); itr++)
	{	
		unsigned count = 0;
		for(vector<string>::iterator itr1 = market_calendar_vector.begin(); itr1 != market_calendar_vector.end(); itr1++)
		{
			if ((*itr1).compare(*itr)>0) 
			{
				
				count++;
				if (count == N || itr1 == market_calendar_vector.end()-1)
				{
					end_date_map[*itr] = *itr1;
					break;
				}
			} 
		}
		
		count = 0;
		for(vector<string>::reverse_iterator itr2 = market_calendar_vector.rbegin(); itr2 != market_calendar_vector.rend(); itr2++)
		{
			if ((*itr2).compare(*itr)<0) 
			{
				count++;
				if (count == N || itr2 == market_calendar_vector.rend()-1)
				{
					start_date_map[*itr] = *itr2;
					break;
				}
			}
		}
	}
}


void EODMarketData::populate_stock_data_map_from_web(vector<string> symbol_vector, map<string, Stock_data>& data_map)
{
// for every stock in symbol_vector, download data and store stock price data in data_map
// symbol_vector: stocks in EA file
// data_map: key: symbol, value: Stock_data(which is a map, key: date, value: price)
	CURL* handle;
	curl_global_init(CURL_GLOBAL_ALL);// set up the program environment that libcurl needs 
	handle = curl_easy_init();// curl_easy_init() returns a CURL easy handle 

	// if everything's all right with the easy handle... 
	if (handle)
	{
		string symbol = "IWV";
		string start_date;
		string end_date;
		string date;
		
		Stock_data stock_date_price = download_stock_data_from_web(handle, symbol, date, start_date, end_date);
		data_map[symbol] = stock_date_price;
		
		for(unsigned i=0; i<symbol_vector.size(); i++)
		{
			date = EA_date_vector[i];
			symbol = symbol_vector[i];
			start_date = start_date_map[date];
			end_date = end_date_map[date];
			
			Stock_data stock_date_price = download_stock_data_from_web(handle, symbol, date, start_date, end_date);
			if (stock_date_price.size() == 2*N+1) data_map[symbol] = stock_date_price;
		}
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
	}
	curl_easy_cleanup(handle); // cleanup since you've used curl_easy_init  
	curl_global_cleanup(); // release resources acquired by curl_global_init()
}


Stock_data EODMarketData::download_stock_data_from_web(CURL* handle, string symbol, string date, string start_date, string end_date)
{
// given stock symbol, EA date, start date, end date, download stock prices from start date to end date
// if lack prices in some trading days, re download historical data from default start date and select 2n+1 dates 
	string url_common = "https://eodhistoricaldata.com/api/eod/";
	string api_token = "639e17ec546a07.79232501";  // You must replace this API token with yours
	string url_request;
	if (start_date.empty() && end_date.empty())
	{
		url_request = url_common + symbol + ".US?" + "from=" + default_start_date + "&api_token=" + api_token + "&period=d";
	}
	else
	{
		url_request = url_common + symbol + ".US?" + "from=" + start_date + "&to=" + end_date + "&api_token=" + api_token + "&period=d";
	}
	Stock_data stock_date_price;
			
	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;
	
	curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
	curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

	CURLcode result;
	result = curl_easy_perform(handle);// perform, then store the expected code in result
	if (result != CURLE_OK)
	{
		// if errors have occured, tell us what is wrong with result
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
	}
	
	stringstream sData;
	sData.str(data.memory);
	string sValue, sDate;
	double dValue = 0;
	string line;
	
	while (getline(sData, line)) {
		size_t found = line.find('-');
		if (found != std::string::npos)
		{
			sDate = line.substr(0, line.find_first_of(','));
			line.erase(line.find_last_of(','));
			sValue = line.substr(line.find_last_of(',') + 1);
			dValue = strtod(sValue.c_str(), NULL);
			stock_date_price[sDate] = dValue;
		}
	}
	
	free(data.memory);
	data.size = 0;
	if (stock_date_price.size() != 2*N+1 && !start_date.empty()) 
	{
		start_date = "";
		end_date = "";
		stock_date_price = download_stock_data_from_web(handle, symbol, date, start_date, end_date);
		
		Stock_data new_stock_date_price;
		unsigned count = 0;
		for(Stock_data::iterator itr = stock_date_price.begin(); itr != stock_date_price.end(); itr++)
		{
			if ((itr->first).compare(date)>=0) 
			{
				count++;
				new_stock_date_price[itr->first] = itr->second;
				if (count == N+1 || itr == --stock_date_price.end()) break;
			} 
		}
		
		count = 0;
		for(Stock_data::reverse_iterator itr = stock_date_price.rbegin(); itr != stock_date_price.rend(); itr++)
		{
			if ((itr->first).compare(date)<0) 
			{
				count++;
				new_stock_date_price[itr->first] = itr->second;
				if (count == N || itr == --stock_date_price.rend()) break;
			}
		}
		if (new_stock_date_price.size() < 2*N+1) cout << "Downloading Reminder: There are only " << new_stock_date_price.size() << " historical prices for " + symbol << endl;
		return new_stock_date_price;
	}
	return stock_date_price;
}
