#include <iostream>
#include <fstream>
#include "curl/curl.h"

using namespace std;

struct MemoryStruct {
    char* memory;
    size_t size;
};

//static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
//{
//    size_t realsize = size * nmemb;
//    struct MemoryStruct* mem = (struct MemoryStruct*)userp;
//
//    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
//    if (!ptr) {
//        /* out of memory! */
//        printf("not enough memory (realloc returned NULL)\n");
//        return 0;
//    }
//
//    mem->memory = ptr;
//    memcpy(&(mem->memory[mem->size]), contents, realsize);
//    mem->size += realsize;
//    mem->memory[mem->size] = 0;
//
//    return realsize;
//}

void WriteMemory(void* contents, size_t size, size_t nmemb, void* userp) {
    cout << userp << endl;
}

int main() {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl, CURLOPT_URL, "https://apidojo-yahoo-finance-v1.p.rapidapi.com/stock/v2/get-summary?symbol=TSLA&region=US");

    struct curl_slist* headers = NULL;
    string response_string;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 90cfc6970fmsh4f148a374b34566p115f3ejsnf121b03c19d2");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: apidojo-yahoo-finance-v1.p.rapidapi.com");

    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    //FILE * myfile;
    //fopen_s(&myfile, "C:\\Users\\ryanh\\source\\repos\\StockDashboard\\stonk.txt", "w");
    //myfile << "Hello\n";
    


    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemory);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&myfile);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(curl);
    //printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
    //cout << chunk.memory << endl;
    //fclose(myfile);

	return 0;
}