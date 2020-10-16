// g++ string.cpp -std=c++11 -o a.out;./a.out
// g++ string.cpp -std=c++14 -o a.out;./a.out
// g++ string.cpp -std=c++14 -I../common -o a.out;./a.out



#include <iostream>
#include <string>
#include <regex>


void case1()
{
    using namespace std;
    {
        string str = "abc";
        cout << str.length() << endl;
        cout <<str.substr(0, 1) <<endl;
        cout << str[1] <<endl;
        cout << "index of a: " << str.find("a") <<endl;
        cout << string::npos << endl;
        cout << (str.find("2") == string::npos) << endl;
        cout << str + "d" <<endl;

    } // namespace std;
    
}

void case2()
{
    using namespace std::literals::string_literals;  // C++ 14 
    {
        using std::string;
        using namespace std;
        auto str = "hello world"s;
        cout << str.length() <<endl;
        cout << "time"s.size() <<endl;
    } // namespace std::literals::string_literals;
    
}

void case3()
{
    using namespace std;
    // 原始字符
    auto str = R"(nier:automata)";
    auto str1 = R"(char""'')";
    auto str2 = R"(\r\n\t)";
    auto str3 = R"(\\\$)";
    auto str4 = "\\\\\\$";

    auto str5 = R"==(R"(xxx)")==";

    cout << str <<endl;
    cout <<str1 <<endl;
    cout <<str2 <<endl;
    cout <<str3 <<endl;
    cout <<str4 <<endl;
    cout <<str5 <<endl;

}

void case4() 
{
    using namespace std;
    
    cout << stoi("42") <<endl;
    cout << stol("3") <<endl;
    cout << stod("5") <<endl;

    cout << to_string(stol("782323")) <<endl;

}

// 字符串视图
class my_string_view final
{
    public:
        using this_type = my_string_view;
        using string_type = std::string;
        using string_ref_type = std::string&;

        using char_ptr_type = const char*;
        using size_type = size_t;

    private:
        char_ptr_type ptr = nullptr;
        size_type len = 0;
    
    public:
        my_string_view() = default;
        ~my_string_view() = default;

        my_string_view(string_ref_type str) noexcept
            : ptr(str.data()), len(str.length())
        {}
    public:
        char_ptr_type data() const
        {
            return ptr;
        }
        size_type size() const
        {
            return len;
        }
};

/// 正则表达
static
auto make_regex = [](const auto& txt)
{
    return std::regex(txt);
};

static
auto make_match = []()
{
    return std::smatch();
};

void case5()
{
    using namespace std;

    auto str = "neir:automata"s;

    auto reg = make_regex(R"(^(\w+):(\w+)$)");
    auto what = make_match();

    cout<< regex_match(str, what, reg) <<endl;

    for(const auto& x: what){
        cout << x << ",";
    }
    cout <<endl;

    cout << what.length() <<endl;
}

void case6()
{
    using namespace std;

    auto str = "god of war"s;
    auto reg = make_regex(R"(\w\s)");
    auto what = make_match();

    auto found = regex_match(str, what, reg);

    cout << "匹配结果：" << (found ? "匹配成功" : "匹配失败") <<endl;
    cout << what.empty() <<endl;
    cout << what.length() <<endl;
    
    for (const auto& s: what) {
        cout << s << ",";
    }
    cout <<endl;

    for (int i = 0; i < what.length(); i++) {
        cout << what[i] << ",";
    }
    cout <<endl;

    auto new_str = regex_replace(
        str,
        make_regex(R"(\w+$)"), 
        "somestring"
    );

    cout << new_str << endl;
}

int main() 
{
    // case1();

    // case2();

    // case3();

    // case4();

    // case5();

    case6();

    return 0;
}