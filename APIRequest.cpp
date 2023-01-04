#include "APIRequest.h"

APIRequest::APIRequest() {};

CURL* APIRequest::initializeAPIRequest() {
	CURL * curl = curl_easy_init();
	return curl;
}

void APIRequest::setRequestOptionsStock(CURL* curl, FILE * fp, string requestType, string symbol, string region) {
	_symbol = symbol;
	_region = region;
	_requestType = requestType;

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	string finalURL = _prefix + _requestType + "?" + "symbol=" + _symbol + "&region=" + _region;
	curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
}

void APIRequest::setRequestOptionsChart(CURL* curl, FILE* fp, string requestType, string symbol, string region, string interval, string range) {
	_symbol = symbol;
	_region = region;
	_requestType = requestType;
	_interval = interval;
	_range = range;

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	string finalURL = _prefix + _requestType + "?" + "interval=" + _interval + "&symbol=" + _symbol + "&range=" + _range + "&region=" + _region;
	curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
}

void APIRequest::setRequestHeaders(CURL* curl) {
	char* buf = nullptr;
	size_t size = 1;
	errno_t k = _dupenv_s(&buf, &size, "API");
	string keyPrefix = "X-RapidAPI-Key: ";
	string key = buf;
	string finalKey = keyPrefix + key;
	free(buf);

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, finalKey.c_str());
	headers = curl_slist_append(headers, _apihost.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}

CURLcode APIRequest::performRequest(CURL* curl) {
	CURLcode res = curl_easy_perform(curl);
	return res;
}