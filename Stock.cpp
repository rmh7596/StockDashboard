#include "Stock.h"

Stock::Stock() {
	_ticker = " ";
	_preMarket = 0;
	_postMarket = 0;
	_marketCap = 0;
}

Stock::~Stock() {}

void Stock::Deserialize(const std::string& filePath)
{
	FILE* myfile;

	fopen_s(&myfile, filePath.c_str(), "r");

	rapidjson::Document document;

	char readBuffer[65536];
	rapidjson::FileReadStream is(myfile, readBuffer, sizeof(readBuffer));

	document.ParseStream(is);
	assert(document.IsObject());

	rapidjson::Value& price = document["price"];
	rapidjson::Value& preMarket = price["preMarketPrice"];
	rapidjson::Value& postMarket = price["postMarketPrice"];
	rapidjson::Value& regularMarketPrice = price["regularMarketPrice"];

	rapidjson::Value& marketCap = price["marketCap"];
	
	rapidjson::Value& quoteType = document["quoteType"];

	_ticker = quoteType["symbol"].GetString();
	if (preMarket.HasMember("raw")) { // Will throw assertion error if the market is not open
		_preMarket = preMarket["raw"].GetFloat();
	}
	

	if (postMarket.HasMember("raw")) { // Will throw assertion error if the market is not closed
		_postMarket = postMarket["raw"].GetFloat();
	}
	
	_marketCap = marketCap["raw"].GetFloat();
	_regularMarketPrice = regularMarketPrice["raw"].GetFloat();

	fclose(myfile);
}

std::string Stock::getTicker() {
	return Stock::_ticker;
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

double Stock::getMarketCap() {
	return Stock::_marketCap;
}