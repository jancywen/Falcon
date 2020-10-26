#include <iostream>
#include <map>

#include <unordered_map>

class TestContainer final
{
private:
    std::map<std::string, std::string> m_map;

public:
    TestContainer() = default;
    ~TestContainer() = default;

public:
    void add_some(const std::string & s)
    {
        if (m_map.find(s) == m_map.end()) 
        {
            m_map[s] = s;
        }
        
    }

    void debug_print() {
        for(auto x: m_map) {
            std::cout <<x.first<< std::endl;
            std::cout << x.second <<std::endl;
        }
    }

};

int main()
{
    TestContainer test;
    test.add_some("123");
    test.debug_print();

}
