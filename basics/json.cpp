// g++ json.cpp -std=c++14 -I../common

#include <iostream>
#include <vector>
#include <map>

#include "json.hpp"

using namespace std;

using json_t = nlohmann::json;

void case1()
{
    json_t j;
    j["age"] = 32;
    j["name"] = "super man";
    j["gear"]["suits"] = "2009";
    j["dogs"] = {"dog1", "dog2"};

    vector<int> v = {1, 2, 3};
    j["numbers"] = v;

    map<string, int> m = {{"one", 1}, {"two", 2}};
    j["kv"] = m;

    cout <<j.dump() <<endl;
    cout << j.dump(2) <<endl;


    json_t j1 = {
        {"age", 23},
        {"name", "spiderman"},
        {"jobs", {"superhero", "neighborhood"}},
        {"gear", {"suits", "2099"}}
    };

    cout << j1.dump(2) << endl;     // 序列化 2个缩进
}

void case2() 
{
    string str = R"({
        "name": "peter",
        "age" : 23,
        "married" : true
    })";
    auto j = json_t::parse(str);    //反序列化
    cout <<j.dump(2) <<endl;
}

void case3()
{
    auto txt = "bad:data"s;   // 不是正确的JSON数据
    try
    {
        auto j = json_t::parse(txt);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void case4()
{
    json_t j_sting = "this is a string";
    auto cpp_string = j_sting.get<std::string>();

    std::string cpp_string2;
    j_sting.get_to(cpp_string2);

    std::string serialized_string = j_sting.dump();

    cout << cpp_string << "==" << cpp_string2 << "==" << j_sting.get<std::string>() << endl;

    // output of serialized value
    std::cout << j_sting << " == " << serialized_string << std::endl;
}

void json1()
{


}
int main()
{

    // case1();
    // case2();
    // case3();
    case4();
    return 0;
}