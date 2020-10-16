#include <iostream>
#include <regex>

using namespace std;


template<class T, class... Args>
std::unique_ptr<T>
my_make_unique(Args&&... args) {
    return std::unique_ptr<T>(
        new T(std::forward<Args>(args)...)
    );
}

void case1() 
{
    using namespace std;
    {
        unique_ptr<int> ptr1(new int(10));
        cout << *ptr1 << endl;

        unique_ptr<string> ptr2(new string("hello world"));
        cout << *ptr2 <<endl;
        cout << ptr2->size() << endl;

        auto ptr3 = make_unique<int>(42);
        cout << *ptr3 <<endl;

        auto ptr4 = make_unique<string>("god of war");
        cout <<ptr4->empty() <<endl;

        auto ptr5 = my_make_unique<long>(100L);
        cout <<*ptr5 <<endl;

    } // namespace std;
    
}


void case2()
{
    using namespace std;
    {
        auto ptr1 = make_unique<int>(42);

        cout <<*ptr1 <<endl;

        auto ptr2 = std::move(ptr1);


        if (!ptr1) {
            cout <<"ptr1 is null" <<endl;
        }

        cout << *ptr2 <<endl;

    } // namespace std;
    
}

void case3()
{
    using namespace std;
    {
        shared_ptr<int> ptr1(new int(10));
        cout << *ptr1 <<endl;

        shared_ptr<string> ptr2(new string("hello"));
        cout << *ptr2 <<endl;

        auto ptr3 = make_shared<int>(42);
        cout << *ptr3 <<endl;

        auto ptr4 = make_shared<string>("wells");
        cout << *ptr4 <<endl;
        cout << ptr4->empty() <<endl;
    } // namespace std;
    
}

void case4()
{
    using namespace std;
    {
        auto ptr1 = make_shared<int>(42);
        cout << ptr1.unique() << endl; // 唯一性

        auto ptr2 = ptr1; //直接赋值

        // ptr1、ptr2 都不唯一，且引用计数为 2
        cout<< ptr1.unique() <<endl;
        cout <<ptr1.use_count() <<endl;
        cout << ptr2.unique() <<endl;
        cout << ptr2.use_count() <<endl;

    } // namespace std;
    
}



class Node final
{
    public:
        using this_type = Node;
        using shared_type = std::weak_ptr<this_type>;
    public:
        shared_type next;
    public:
        Node() = default;
        ~Node()
        {
            using namespace std;
            cout <<"node dtor" <<endl;
        }
};

void somefunc() 
{
    auto n1 = make_shared<Node>();
    auto n2 = make_shared<Node>();

    cout<< n1.use_count() << endl;
    cout<< n2.use_count() <<endl;

    // 两个节点互指，形成了循环引用
    n1->next = n2;
    n2->next = n1;
    // 因为使用了weak_ptr，引用计数为1
    cout << n2.use_count() << endl;

    if (!n1->next.expired()) { // 检查指针是否有效
        auto ptr = n1->next.lock(); // lock()获取shared_ptr
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