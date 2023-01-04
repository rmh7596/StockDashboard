#pragma once
#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "APIRequest.h"
#include "curl/curl.h"
#include <vector>

class Stock
{
public:
	Stock();
	virtual ~Stock();
	virtual void DeserializeStock(Stock *s, const std::string& filePath);
	virtual void DeserializeChart(Stock* s, const std::string& filePath);
	void getStockData(char *symbolBuf);
	void getStockChart(std::string interval, std::string range);
	std::string getTicker();
	std::string getQuoteType();
	float getRegularMarketPrice();
	float getPreMarket();
	float getPostMarket();
	std::string getMarketCap();
	std::vector<float> getPrices();
	void computeChartBounds();
	float getMaxPrice();
	float getMinPrice();
	const string requestDataPath = "C:\\Users\\ryanh\\source\\repos\\StockDashboard\\stonk.json";
private:
	std::string _ticker;
	std::string _quoteType;
	float _regularMarketPrice = 0;
	float _preMarket;
	float _postMarket;
	std::string _marketCap;
	std::vector<float> _prices;
	float _maxPrice;
	float _minPrice;
	void setTicker(std::string ticker);
	void setQuoteType(std::string quoteType);
	void setRegularMarketPrice(float regularMarketPrice);
	void setPreMarket(float preMarket);
	void setPostMarket(float postMarket);
	void setMarketCap(std::string marketCap);
};

