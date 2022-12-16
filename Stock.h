#pragma once
#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class Stock
{
public:
	Stock();
	virtual ~Stock();
	virtual void Deserialize(const std::string& filePath);
	std::string getTicker();
	float getRegularMarketPrice();
	float getPreMarket();
	float getPostMarket();
	double getMarketCap();
private:
	std::string _ticker;
	float _regularMarketPrice;
	float _preMarket;
	float _postMarket;
	double _marketCap;
};

