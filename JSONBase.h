#pragma once
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"	// wrapper of C stream for prettywriter as output
#include "rapidjson/prettywriter.h"	// for stringify JSON
class JSONBase
{
public:
	bool DeserializeFromFile(const std::string& filePath);
};

