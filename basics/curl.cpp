



#include <iostream>

#include <curl/curl.h>

using namespace std;


void case1()
{
    auto curl = curl_easy_init();       //创建一个句柄，类型是 CURL*

    curl_easy_setopt(curl, CURLOPT_URL, "http://nginx.org");    // 设置请求URI

    auto res = curl_easy_perform(curl);     // 发送数据
    if (res != CURLE_OK) { // 检查是否执行成功 
        cout << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl); // 清理句柄相关的资源
}

size_t write_callback(char*ptr, size_t size, size_t nmemb, void* );

void case2() 
{
    auto url  = curl_easy_init();
    
    decltype(&write_callback) f = 
        [](char*ptr, size_t size, size_t nmemb, void* userdata)
        {
            cout << "size = " <<size *nmemb <<endl;
            return size * nmemb;
        };
    curl_easy_setopt(url, CURLOPT_WRITEFUNCTION, f);

    auto res = curl_easy_perform(url);
    if (res != CURLE_OK) {
        cout << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(url);
}

int main()
{
    curl_global_init(CURL_GLOBAL_SSL);

    // case1();


    case2();
    cout << curl_version() <<endl;

    return 0;
}