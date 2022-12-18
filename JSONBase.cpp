#include "JSONBase.h"

using namespace rapidjson;

bool DeserializeFromFile(const std::string& filePath) {
    FILE* myfile;

    fopen_s(&myfile, filePath.c_str(), "w");

	Document document;

	char readBuffer[100];
	FileReadStream is(myfile, readBuffer, sizeof(readBuffer));

	document.ParseStream(is);
	assert(document.IsObject());

	rapidjson::Value& results = document["price"];
	rapidjson::Value& preMarket = results["preMarketPrice"];
	rapidjson::Value& raw = preMarket["raw"];

    fclose(myfile);

	return true;
}