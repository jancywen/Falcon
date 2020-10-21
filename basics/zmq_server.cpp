// g++ zmq_server.cpp -std=c++14 -lzmq -lpthread -I../common -o zmq_server


#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#include <zmq.hpp>


int main()
{
    using namespace std::chrono_literals;

    zmq::context_t context{1};

    zmq::socket_t socket{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");

    const std::string data{"World"};

    for(;;)
    {
        zmq::message_t request;

        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received " <<request.to_string() <<std::endl;

        std::this_thread::sleep_for(1s);

        socket.send(zmq::buffer(data), zmq::send_flags::none);
    }
}