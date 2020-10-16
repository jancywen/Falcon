#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Point final
{
    public:
        int x = 0;
    public:
        Point(int a)noexcept :x(a)
        {
            cout << "ctor" << x <<endl;
        }
        Point() noexcept
        {
            cout << "ctor" <<x <<endl;
        }
        ~Point() noexcept
        {
            cout <<"dtor" << x <<endl;
        }
        
        Point(const Point& p) noexcept
        {
            x = std::move(p.x);
            cout << "move ctor" << x <<endl;
        }

        Point(Point&& p) noexcept
        {
            x = std::move(p.x);
            cout << "move cotr" <<x<<endl;
        }
};

void case1()
{
    vector<Point> v;
    v.reserve(10);

    Point p;
    v.push_back(p); // 存储对象，拷贝构造，成本很高
    v.push_back(std::move(p)); // 定义转移构造后就可以转移存储，降低成本

    v.emplace_back(1); // 直接在容器里构造元素，不需要拷贝或者转移

    for (auto& p: v) {
        cout << p.x << endl;
    }
}

void case2() 
{
    array<int, 2> arr;
    cout << arr.size() <<endl;

    vector<int> v(2);
    for (int i = 0; i< 10; i++) {
        v.emplace_back(i);
    }
    cout << v.size() << endl;

    deque<int> d;
    d.emplace_back(9);
    d.emplace_front(1);
    cout << d.size() <<endl;

}

bool operator<(const Point& a, const Point& b)
{
    return a.x < b.x;
}
void case3()
{
    set<Point> s;
    s.emplace(3);
    s.emplace(7);
    s.emplace(5);

    for (auto& p: s) {
        cout << p.x << ",";
    }
    cout <<endl;
}

void case4()
{
    set<int> s = {7, 3, 9};
    for(auto& a: s){
        cout << a << ",";
    }
    cout <<endl;

    auto comp = [](auto a, auto b)
    {
        return a > b;
    };

    set< int, decltype(comp)> gs(comp); // 在容器的模板参数里指定 比较函数
    std::copy(begin(s), end(s), inserter(gs, gs.end())); // 使用插入迭代器 拷贝数据

    for (auto& a: gs) {
        cout << a << ",";
    }
    cout << endl;

}

void case5() 
{
    map<string, string> m;
    m["key1"] = "value1";
    m.emplace("key4", "value4");
    m["key3"] = "value3";

    for (auto& a : m) {
        cout << a.first << " : " << a.second << ",   ";
    }
    cout <<endl;

}

void case6()
{
    using map_type = unordered_map<int, string>;
    map_type dict;

    dict[1] = "one";
    dict.emplace(3, "three");
    dict[10] = "ten";

    for (auto& a : dict) {
        cout << a.first << ": " << a.second << ",";
    }
    cout <<endl;
}

bool operator==(const Point&a, const Point&b)
{
    return a.x == b.x;
}

void case7()
{
    auto hasher = [](const auto& p)
    {
        return std::hash<int>()(p.x);
    };

    unordered_set<Point, decltype(hasher)> s(10, hasher);

    s.emplace(3);
    s.emplace(7);
    s.emplace(100);

    for(auto & p: s) {
        cout << p.x << ",";
    }
    cout << endl;
}


int main()
{
    // case1();
    // case2();
    // case3();
    // case4();
    // case5();
    // case6();
    case7();

    return 0;
}