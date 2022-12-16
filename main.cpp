#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "curl/curl.h"
#include "Stock.h"

using namespace std;

int main() {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://apidojo-yahoo-finance-v1.p.rapidapi.com/stock/v2/get-summary?symbol=TSLA&region=US");

    struct curl_slist* headers = NULL;
    
    char* buf = nullptr;
    size_t size = 1;

    errno_t k = _dupenv_s(&buf, &size, "API");
    string keyPrefix = "X-RapidAPI-Key: ";
    string key = buf;
    string finalKey = keyPrefix + key;
    free(buf);

    headers = curl_slist_append(headers, finalKey.c_str());
    headers = curl_slist_append(headers, "X-RapidAPI-Host: apidojo-yahoo-finance-v1.p.rapidapi.com");

    FILE * myfile;
    
    fopen_s(&myfile, "C:\\Users\\ryanh\\source\\repos\\StockDashboard\\stonk.json", "w");
   
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, myfile);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(curl);
    
    fclose(myfile);
    
    Stock n = Stock();
    n.Deserialize("C:\\Users\\ryanh\\source\\repos\\StockDashboard\\stonk.json");
    
    //fclose(myfile);

    cout << n.getTicker() << endl;
    cout << n.getRegularMarketPrice() << endl;
    cout << n.getPreMarket() << endl;
    cout << n.getPostMarket() << endl;
    cout << n.getMarketCap() << endl;

	return 0;
}