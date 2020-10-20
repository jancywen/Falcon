// source include
// git clone https://github.com/msgpack/msgpack-c.git
// g++ msgpack.cpp -std=c++14 -I../common/include -o a.out

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <msgpack.hpp>

#if MSGPACK_VERSION_MAJOR < 2
# error "msgpack  is too old."
#endif

using namespace std;

void case1()
{
    vector<int> v = {1, 2, 3, 4, 5};

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, v);

    cout << "data:" << sbuf.data() 
    << "size" << sbuf.size() <<endl;

    msgpack :: object_handle oh = msgpack::unpack(sbuf.data(), sbuf.size());
    msgpack::object obj = oh.get();
    cout <<obj<<endl;

    vector<int> v1;
    obj.convert(v1);
    for (int& i: v1) {
        cout << i << ",";
    }
    cout << endl;
}

void case2() 
{
    msgpack::sbuffer sbuf;
    msgpack::packer<decltype(sbuf)> packer(sbuf);

    packer.pack(10).pack("monado"s).pack(vector<int>{1, 2, 4});

    cout <<sbuf.size()<< endl;

    for (decltype(sbuf.size()) offset = 0; offset != sbuf.size();) {
        auto handler = msgpack::unpack(sbuf.data(), sbuf.size(), offset);
        auto obj = handler.get();
        cout << obj <<endl;
    }

}


class Book final
{
public:
    int         id;
    string      title;
    set<string> tags;
public:
    MSGPACK_DEFINE(id, title, tags);

};

void case3()
{
    
    Book book1 = {1, "some", {"iOS", "iPhone"}};

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, book1);

    auto obj = msgpack::unpack(sbuf.data(), sbuf.size()).get();

    cout <<obj <<endl;

    Book book2;
    obj.convert(book2);

    cout <<book2.title<< endl;

}

int main()
{

    // case1();
    // case2();
    case3();
    return 0;
}