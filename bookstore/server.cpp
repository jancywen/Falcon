
// g++ server.cpp -std=c++14 -I../common -I../common/include -I/usr/local/include/luajit-2.1 -lluajit-5.1 -ldl -lzmq -lpthread -o s.out

#include "cpplang.hpp"
#include "Summary.hpp"
#include "Zmq.hpp"
#include "Config.hpp"

#include "json.hpp"

extern "C" {
    #include <luajit-2.1/luajit.h>
    #include <luajit-2.1/lualib.h>
    #include <luajit-2.1/lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>

#include <msgpack.hpp>
#include "SalesData.hpp"
#include <atomic>


USING_NAMESPACE(std);
USING_NAMESPACE(cpp_study);


static
auto debug_print = [](auto&b)
{
    using json_t = nlohmann::json;

    json_t j;

    j["id"] = b.id();
    j["sold"] = b.sold();
    j["revenue"] = b.revenue();

    std::cout <<j.dump(2) << std::endl;
};

int main()
try
{
    cout << "hello cpp study server" <<endl;

    
    auto get = [](std::string key) {
        cout << "log" <<endl;
        auto reg = std::regex(R"(^(\w+)\.(\w+)$)");
        auto match = std::smatch();
        assert(regex_match(key, match, reg));
        
        auto p_conf = match[1];
        auto p_key = match[2];

        std::shared_ptr<lua_State> vm(luaL_newstate(), lua_close);
        luaL_openlibs(vm.get());

        int status;
        status = luaL_dofile(vm.get(), "./conf.lua");
        assert(status == 0);

        using namespace luabridge;

        auto config = getGlobal(vm.get(), p_conf.str().c_str());

        // std::cout <<config[p_key.str()]<<std::endl;


        return config[p_key.str()].tostring();
    };

    auto addr = get("config.zmq_ipc_addr");
    
    cout << addr << endl;

    Summary sum;
    std::atomic_int count {0};

    auto recv_cycle = [&]()
    {
        using zmq_ctx = ZmqContext<1>;

        auto sock = zmq_ctx::recv_sock();

        sock.bind(addr);
        assert(sock.connected());
#if 0
        for(;;) {
            auto msg_ptr = std::make_shared<zmq_message_type>();

            sock.recv(msg_ptr.get());
std::cout <<"msg_ptr->size()" <<  msg_ptr->size() <<endl;
            std::thread(
                [&sum, msg_ptr]() 
            {
                SalesData book;

                auto obj = msgpack::unpack(msg_ptr->data<char>(), msg_ptr->size()).get();
                obj.convert(book);

                debug_print(book);
                sum.add_sales(book);

            }).detach();
        }
#endif

        for(;;) {
            auto msg_ptr = std::make_shared<zmq_message_type>();

            zmq::message_t request;
            sock.recv(request, zmq::recv_flags::dontwait);

            auto func = [&]() {
                SalesData book;
                auto obj = msgpack::unpack(request.data<char>(), request.size()).get();
                obj.convert(book);
                debug_print(book);
                sum.add_sales(book);
            };

            if (request.size() > 0) {
                // std::thread(func).detach();
                ++count;
                func();
            }
        }

    };

    auto log_cycle = [&]()
    {
        for(;;) {
            std::this_thread::sleep_for(5s);
            using json_t = nlohmann::json;
            json_t j;
        
            j["count"] = static_cast<int>(count);
            j["minmax"] = sum.minmax_sales();

            std::cout<< j.dump(2) << std::endl;
        }
    };

    // launch log_cycle
    auto fu1 = std::async(std::launch::async, log_cycle);

    auto recvf = std::async(std::launch::async, recv_cycle);
    recvf.wait();
} 
catch (std::exception& e)
{
    std::cout << "error: "<< e.what() <<std::endl;
}
