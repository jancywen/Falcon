#include <iostream>
#include <vector>

using namespace std;

auto f1 = [](){};

auto f2 = []()
{
    cout << "lambda f2" <<endl;

    auto f3 = [](int x)     //嵌套定义一个 lambda
    {
        return x * x;
    };

    cout << f3(10) << endl;
};


int main()
{

    vector<int> v = {};
    cout << *find_if(begin(v), end(v), [](int x){return x >= 5;}) <<endl;


    using namespace std::literals::string_literals;
    auto str = "hello world"s;
    str.size();

    
    return 0;
}