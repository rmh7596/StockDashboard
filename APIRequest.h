#pragma once
#include "curl/curl.h"
#include <iostream>

using namespace std;

class APIRequest
{
public:
	APIRequest();
	CURL* initializeAPIRequest();
	void setRequestOptions(CURL* curl, FILE * fp, string requestType, string symbol, string region);
	void setRequestHeaders(CURL* curl);
	CURLcode performRequest(CURL * curl);

private:
	string _symbol;
	string _region;
	string _requestType;
	FILE* fp;
	const string _prefix = "https://apidojo-yahoo-finance-v1.p.rapidapi.com/stock/v2/";
	const string _apihost = "X-RapidAPI-Host: apidojo-yahoo-finance-v1.p.rapidapi.com";
};

