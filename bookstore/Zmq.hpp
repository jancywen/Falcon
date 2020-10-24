
#ifndef _ZMQ_HPP
#define _ZMQ_HPP

#include "cpplang.hpp"

#include <zmq.hpp>

BEGIN_NAMESPACE(cpp_study)

using zmq_context_type = zmq::context_t;
using zmq_socket_type = zmq::socket_t;
using zmq_message_type = zmq::message_t;

template<int thread_num = 1>                // 使用整数模板参数来指定线程数
class ZmqContext final
{

public:
    ZmqContext() = default;
    ~ZmqContext() = default;

public:
    static                                  // 静态成员函数代替静态成员变量
    zmq_context_type& context()
    {
        static zmq_context_type ctx(thread_num);
        return ctx;
    }

    static
    zmq_socket_type recv_sock(int hwm = 1000, int linger = 10)
    {
        zmq_socket_type sock(context(), zmq::socket_type::pull);

        zmq_setsockopt(sock, ZMQ_RCVHWM, &hwm, sizeof(hwm));
        zmq_setsockopt(sock, ZMQ_LINGER, &linger, sizeof(linger));

        return sock;
    }

    static 
    zmq_socket_type send_sock(int hwm = 1000, int linger = 10)
    {
        zmq_socket_type sock(context(), zmq::socket_type::push);
        
        zmq_setsockopt(sock, ZMQ_RCVHWM, &hwm, sizeof(hwm));
        zmq_setsockopt(sock, ZMQ_LINGER, &linger, sizeof(linger));

        return sock;
    }
};

END_NAMESPACE(cpp_study)


#endif