#pragma once

#include<iostream>
#include <curl/curl.h>
#include <string>
class HTTP
{
private:
	static size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp);

public:
	static std::string GET(std::string url);
};

