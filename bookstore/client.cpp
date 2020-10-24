#include "cpplang.hpp"
#include "SalesData.hpp"

#include "Zmq.hpp"


#include "json.hpp"

USING_NAMESPACE(std);
USING_NAMESPACE(cpp_study);

static
auto debug_print = [](auto& b)
{
    using json_t = nlohmann::json;
    json_t j;

    j["id"] = b.id();
    j["sold"] = b.sold();
    j["revenue"] = b.revenue();

    std::cout << j.dump(2) << std::endl;
};

static 
auto make_sales = [](const auto& id, auto s, auto r)
{
    return SalesData(id, s, r).pack();
};

static
auto send_sales = [](const auto& buf)
{
    using zmq_ctx = ZmqContext<1>;
    auto sock = zmq_ctx::send_sock();

    sock.connect(CPP_STUDY_URL);
    assert(sock.connected());

    // auto len = sock.send(buf.data(), buf.size());
    // assert(len == buf.size());
    // cout << "send len = " <<len <<endl;

    sock.send(zmq::const_buffer(buf.data(), buf.size()), zmq::send_flags::none);
};

static
auto test1 = [](const auto& addr, const auto& buf)
{
    using zmq_ctx = ZmqContext<1>;
    auto sock = zmq_ctx::send_sock();

    sock.connect(addr);
    assert(sock.connected());

    sock.send(zmq::const_buffer(buf.data(), buf.size()), zmq::send_flags::none);
};


int main()
try 
{
    cout << "hello cpp_study client" <<endl;

    send_sales(make_sales("001", 10, 100));
    cout << "one" << endl;
    std::this_thread::sleep_for(2s);
    send_sales(make_sales("002", 12, 200));
    cout << "two" <<endl;

    test1(CPP_STUDY_URL, make_sales("003", 12, 323));
    cout << "three" <<endl;

}
catch (std::exception& e)
{

    std::cout << "error: "<< e.what() <<std::endl;
}
