#include "Stock.h"
#include <algorithm>


Stock::Stock() {
	_ticker = "";
	_preMarket = 0;
	_postMarket = 0;
	_marketCap = "";
}

Stock::~Stock() {}

void Stock::DeserializeStock(Stock *s, const std::string& filePath)
{
	FILE* myfile;

	fopen_s(&myfile, filePath.c_str(), "r");

	rapidjson::Document document;

	char readBuffer[16384];
	rapidjson::FileReadStream is(myfile, readBuffer, sizeof(readBuffer));

	document.ParseStream(is);
	assert(document.IsObject());

	rapidjson::Value& price = document["price"];
	rapidjson::Value& preMarket = price["preMarketPrice"];
	rapidjson::Value& postMarket = price["postMarketPrice"];
	rapidjson::Value& regularMarketPrice = price["regularMarketPrice"];
	rapidjson::Value& marketCap = price["marketCap"];
	rapidjson::Value& quoteType = document["quoteType"];

	s->setTicker(quoteType["symbol"].GetString());
	if (preMarket.HasMember("raw")) { // Will throw assertion error if the market is not open
		s->setPreMarket(preMarket["raw"].GetFloat());
	}
	

	if (postMarket.HasMember("raw")) { // Will throw assertion error if the market is not closed
		s->setPostMarket(postMarket["raw"].GetFloat());
	}
	
	if (marketCap.HasMember("fmt")) {
		s->setMarketCap(marketCap["fmt"].GetString()); // Does not work for mutual funds
	}
	s->setRegularMarketPrice(regularMarketPrice["raw"].GetFloat());
	s->setQuoteType(price["quoteSourceName"].GetString());

	fclose(myfile);
}

void Stock::DeserializeChart(Stock* s, const std::string& filePath) {
	FILE* myfile;

	fopen_s(&myfile, filePath.c_str(), "r");

	rapidjson::Document document;

	char readBuffer[16384];
	rapidjson::FileReadStream is(myfile, readBuffer, sizeof(readBuffer));

	document.ParseStream(is);
	assert(document.IsObject());

	static const char* kTypeNames[] =
	{ "Null", "False", "True", "Object", "Array", "String", "Number" };

	rapidjson::Value& chart = document["chart"];
	rapidjson::Value& result = chart["result"];
	rapidjson::Value& zero = result[0];
	rapidjson::Value& indicators = zero["indicators"];
	rapidjson::Value& quote = indicators["quote"];
	rapidjson::Value& zero2 = quote[0];
	rapidjson::Value& open = zero2["open"];
	assert(open.IsArray());
	
	s->_prices.clear(); // Remove previous data
	// Potentially costly conversion from rapidjson::Value::array to std::vector
	for (rapidjson::Value::ConstValueIterator itr = open.Begin(); itr != open.End(); ++itr)
		s->_prices.push_back(itr->GetFloat());

	fclose(myfile);
}

void Stock::getStockData(char* symbolBuf) {
	FILE* myfile;
	fopen_s(&myfile, requestDataPath.c_str(), "w");
	APIRequest ar = APIRequest();
	CURL* curl = ar.initializeAPIRequest();
	ar.setRequestOptionsStock(curl, myfile, "get-summary", symbolBuf, "US");
	ar.setRequestHeaders(curl);
	CURLcode result = ar.performRequest(curl);
	fclose(myfile);
	DeserializeStock(this, requestDataPath);
}

void Stock::getStockChart(std::string interval, std::string range) {
	FILE* myfile;
	fopen_s(&myfile, requestDataPath.c_str(), "w");
	APIRequest ar = APIRequest();
	CURL* curl = ar.initializeAPIRequest();
	ar.setRequestOptionsChart(curl, myfile, "get-chart", _ticker, "US", interval, range);
	ar.setRequestHeaders(curl);
	CURLcode result = ar.performRequest(curl);
	fclose(myfile);
	DeserializeChart(this, requestDataPath);
}

void Stock::setTicker(std::string ticker) {
	this->_ticker = ticker;
}

void Stock::setQuoteType(std::string quoteType) {
	this->_quoteType = quoteType;
}
void Stock::setRegularMarketPrice(float regularMarketPrice) {
	this->_regularMarketPrice = regularMarketPrice;
}
void Stock::setPreMarket(float preMarket) {
	this->_preMarket = preMarket;
}
void Stock::setPostMarket(float postMarket) {
	this->_postMarket = postMarket;
}
void Stock::setMarketCap(std::string marketCap) {
	this->_marketCap = marketCap;
}

std::string Stock::getTicker() {
	return Stock::_ticker;
}

std::string Stock::getQuoteType() {
	return Stock::_quoteType;
}

float Stock::getRegularMarketPrice() {
	return Stock::_regularMarketPrice;
}

float Stock::getPreMarket() {
	return Stock::_preMarket;
}

float Stock::getPostMarket() {
	return Stock::_postMarket;
}

std::string Stock::getMarketCap() {
	return Stock::_marketCap;
}

std::vector<float> Stock::getPrices() {
	return Stock::_prices;
}

void Stock::computeChartBounds() {
	this->_maxPrice = *max_element(std::begin(_prices), std::end(_prices));
	this->_minPrice = *min_element(std::begin(_prices), std::end(_prices));
}

float Stock::getMaxPrice() {
	return Stock::_maxPrice;
}

float Stock::getMinPrice() {
	return Stock::_minPrice;
}