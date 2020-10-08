#include "HTTP.h"


size_t HTTP::WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string HTTP::GET(std::string url)
{
	std::string readBuffer;

	curl_global_init(CURL_GLOBAL_ALL);
	CURL* easyhandle = curl_easy_init();

	curl_easy_setopt(easyhandle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

	curl_easy_perform(easyhandle);


	curl_easy_cleanup(easyhandle);
	curl_global_cleanup();

	return readBuffer;
}


