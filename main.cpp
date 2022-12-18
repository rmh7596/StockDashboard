#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "curl/curl.h"
#include "Stock.h"
#include "APIRequest.h"

using namespace std;

const string requestDataPath = "C:\\Users\\ryanh\\source\\repos\\StockDashboard\\stonk.json";

int main() {
    string ticker;
    cout << "Enter Stock Ticker: ";
    cin >> ticker;

    FILE* myfile;

    fopen_s(&myfile, requestDataPath.c_str(), "w");

    APIRequest ar = APIRequest();
    CURL* curl = ar.initializeAPIRequest();
    ar.setRequestOptions(curl, myfile, "get-summary", ticker, "US");
    ar.setRequestHeaders(curl);
    CURLcode result = ar.performRequest(curl);

    fclose(myfile);
    
    Stock n = Stock();
    n.Deserialize(requestDataPath);
    
    //fclose(myfile);

    cout << "Ticker: " << n.getTicker() << endl;
    cout << "Regular Market Price: " << n.getRegularMarketPrice() << endl;
    cout << "PreMarket: " << n.getPreMarket() << endl;
    cout << "PostMarket: " << n.getPostMarket() << endl;
    cout << "MarketCap: " << n.getMarketCap() << endl;

	return 0;
}