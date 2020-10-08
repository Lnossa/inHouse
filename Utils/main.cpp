#include <iostream>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include "Weather.h"
#include "Date.h"

//size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
//{
//	((std::string*)userp)->append((char*)contents, size * nmemb);
//	return size * nmemb;
//}

int main(int argc, char* argv[])
{
//	std::string readBuffer =
//		"[{\"LocalObservationDateTime\":\"2020-04-19T20:37:00+03:00\",\"EpochTime\":1587317820,\"WeatherText\":\"Cloudy\",\"WeatherIcon\":7,\"HasPrecipitation\":false,\"PrecipitationType\":null,\"IsDayTime\":false,\"Temperature\":{\"Metric\":{\"Value\":12.3,\"Unit\":\"C\",\"UnitType\":17},\"Imperial\":{\"Value\":54.0,\"Unit\":\"F\",\"UnitType\":18}},\"MobileLink\":\"http://m.accuweather.com/en/ro/brasov/287345/current-weather/287345?lang=en-us\",\"Link\":\"http://www.accuweather.com/en/ro/brasov/287345/current-weather/287345?lang=en-us\"}]";
//	//"[{\"firstname\":\"Amritpal\",\"lastname\": \"Singh\",\"ss\": 12345678910}]";
//
////curl_global_init(CURL_GLOBAL_ALL);
////CURL* easyhandle = curl_easy_init();
//
////curl_easy_setopt(easyhandle, CURLOPT_URL, 
////	"http://dataservice.accuweather.com//currentconditions/v1/287345?apikey=zt5pWPCZDXJTACHKYAw5mCgjicOVlzJW");
////curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
////curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);
//
////curl_easy_perform(easyhandle);
//
//
////curl_easy_cleanup(easyhandle);
////curl_global_cleanup();
//
//	Json::Reader reader;
//	Json::Value weather;
//
//	readBuffer.erase(0, 1);
//	readBuffer.erase(readBuffer.size() - 1, 1);
//	reader.parse(readBuffer, weather);
//
//
//	std::cout << weather["Temperature"]["Metric"]["Value"].asInt() << std::endl;
//	std::cout << weather["WeatherText"].asString() << std::endl;
/*	Weather w;
	w.fUpdateWeather();

	std::cout << w.fGetTemp() << " " << w.fGetText() << std::endl*/;


	//Date d;
	//const char* x;
	//x = d.fGetTimeAndDateString();

	//std::cout << x;
	return 0;
}