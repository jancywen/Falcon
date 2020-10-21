// g++ zmq_client.cpp -std=c++14 -lzmq -lpthread -I../common -o zmq_client

#include <string>
#include <iostream>

#include <zmq.hpp>

int main()
{

    zmq::context_t context(1);

    zmq::socket_t socket{context, zmq::socket_type::req};
    socket.connect("tcp://localhost:5555");

    const std::string data{"Hello"};

    for (auto request_num = 0; request_num < 10; ++request_num)
    {
        std::cout <<"Sending Hello " <<request_num << "..." <<std::endl;
        socket.send(zmq::buffer(data), zmq::send_flags::none);

        zmq::message_t reply{};
        socket.recv(reply, zmq::recv_flags::none);

        std::cout<< "Received " << reply.to_string();
        std::cout<< " ( " << request_num << ")";
        std::cout << std::endl;

    }
}