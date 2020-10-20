#include <iostream>

#include <string>
#include <vector>
#include <future>
// #include <zmq.h>
#include <zmq_addon.hpp>

using namespace std;

#if 0
const auto thread_num = 1;

zmq::context_t context(thread_num);

auto make_sock = [&](auto mode)
{
    return zmq::socket_t(context, mode);
};


void case1()
{
    const auto addr = "ipc:///dev/shm/zmq.sock"s;

    auto receiver = [=]()
    {
        auto sock = make_sock(zmq::socket_type::pull);

        sock.bind(addr);
        assert(sock.connected());

        zmq::message_t msg;

        sock.recv(&msg);

        cout << msg.size() << endl;

        string s = {msg.data<char>(), msg.size()};
        cout << s << endl;

    };

    auto sender = [=]()
    {
        auto sock = make_sock(zmq::socket_type::push);

        sock.connect(addr);
        assert(sock.connected());

        string s = "hello zmq";
        //zmq::message_t msg(begin(s), end(s));
        //sock.send(msg);

        sock.send(s.data(), s.size());
    };

    sender();
    receiver();
}
#endif

int main()
{
    int a, b, c;
    std::tie(a, b, c) = zmq::version();

    cout << "version = "
         << a << b << c << endl;
    
    // case1();


    zmq::context_t ctx;
    zmq::socket_t sock1(ctx, zmq::socket_type::pair);
    zmq::socket_t sock2(ctx, zmq::socket_type::pair);
    sock1.bind("inproc://test");
    sock2.connect("inproc://test");

    std::array<zmq::const_buffer, 2> send_msgs = {
        zmq::str_buffer("foo"),
        zmq::str_buffer("bar!")
    };
    if (!zmq::send_multipart(sock1, send_msgs))
        return 1;

    std::vector<zmq::message_t> recv_msgs;
    const auto ret = zmq::recv_multipart(
        sock2, std::back_inserter(recv_msgs));
    if (!ret)
        return 1;
    std::cout << "Got " << *ret
              << " messages" << std::endl;



    cout << "zmq demo" << endl;
}