#pragma once
#include "curl/curl.h"
#include <iostream>

using namespace std;

class APIRequest
{
public:
	APIRequest();
	CURL* initializeAPIRequest();
	void setRequestOptionsStock(CURL* curl, FILE * fp, string requestType, string symbol, string region);
	void setRequestOptionsChart(CURL* curl, FILE* fp, string requestType, string symbol, string region, string interval, string range);
	void setRequestHeaders(CURL* curl);
	CURLcode performRequest(CURL * curl);

private:
	string _symbol;
	string _region;
	string _requestType;
	string _interval; // One of the following is allowed 1m|2m|5m|15m|60m|1d
	string _range; // One of the following is allowed 1d|5d|1mo|3mo|6mo|1y|2y|5y|10y|ytd|max
	FILE* fp;
	const string _prefix = "https://apidojo-yahoo-finance-v1.p.rapidapi.com/stock/v2/";
	const string _apihost = "X-RapidAPI-Host: apidojo-yahoo-finance-v1.p.rapidapi.com";
};

