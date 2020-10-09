#include <iostream>
#include <regex>

using namespace std;


class Node final
{
    public:
        using this_type = Node;
        using shared_type = std::weak_ptr<this_type>;
    public:
        shared_type next;
};

void somefunc() 
{
    auto n1 = make_shared<Node>();
    auto n2 = make_shared<Node>();

    cout<< n1.use_count() << endl;
    cout<< n2.use_count() <<endl;

    n1->next = n2;
    n2->next = n1;

    cout << n2.use_count() << endl;

    if (!n1->next.expired()) {
        auto ptr = n1->next.lock();
        cout << (ptr == n2) << endl;
    }
}


auto make_regex = [](const auto& txt) // 生产正则表达式
{ 
    return std::regex(txt);
};
auto make_match = []() // 生产正则匹配结果
    { 
        return std::smatch();
    };

int main() 
{

#ifdef 0
unique_ptr<int> ptr1(new int(10));      // int智能指针
assert(*ptr1 == 10);                     // 可以使用*取内容
assert(ptr1 != nullptr);                // 可以判断是否为空指针

ptr1.get();

unique_ptr<string> ptr2(new string("hello"));  // string智能指针
assert(*ptr2 == "hello");                // 可以使用*取内容
assert(ptr2->size() == 5);               // 可以使用->调用成员函数
    
    auto ptr3 = std::make_unique<int>(42);

    auto ptr4 = make_unique<string>("god for war");
    ptr4->empty();
#endif


auto str = "god of war"s;             // 待匹配的字符串

auto reg  = 
  make_regex(R"((\w+)\s(\w+))");    // 原始字符串定义正则表达式
auto what = make_match();          // 准备获取匹配的结果

auto found = regex_search(          // 正则查找，和匹配类似
                str, what, reg);

for(const auto& w : what)
{
    cout << w <<endl;
}

assert(found);                        // 断言找到匹配
assert(!what.empty());                // 断言有匹配结果
assert(what[1] == "god");              // 看第一个子表达式
assert(what[2] == "of");              // 看第二个子表达式

auto new_str = regex_replace(      // 正则替换，返回新字符串
    str,                           // 原字符串不改动
    make_regex(R"(\w+$)"),         // 就地生成正则表达式对象
    "peace"                        // 需要指定替换的文字
);

cout << new_str << endl;          // 输出god of peace

    return 0;
}