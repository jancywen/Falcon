// g++ zmq.cpp -std=c++14 -lzmq -lpthread -I../common -o zmq

#include <iostream>

#include <string>
#include <vector>
#include <future>
#include <zmq.h>
#include <zmq_addon.hpp>

using namespace std;

void PublisherThread(zmq::context_t *ctx)
{

    zmq::socket_t publisher(*ctx, zmq::socket_type::pub);
    publisher.bind("inproc://#1");

    std::this_thread::sleep_for(std::chrono::milliseconds(20));

    while (true)    
    {
        publisher.send(zmq::str_buffer("A"), zmq::send_flags::sndmore);
        publisher.send(zmq::str_buffer("Message in A envelope"));
        publisher.send(zmq::str_buffer("B"), zmq::send_flags::sndmore);
        publisher.send(zmq::str_buffer("Message in B envelope"));
        publisher.send(zmq::str_buffer("C"), zmq::send_flags::sndmore);
        publisher.send(zmq::str_buffer("Message in C envelope"));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }   
}

void SubscriberThread1(zmq::context_t *ctx)
{
    zmq::socket_t subscriber(*ctx, zmq::socket_type::sub);
    subscriber.connect("inproc://#1");
    
    subscriber.set(zmq::sockopt::subscribe, "A");
    subscriber.set(zmq::sockopt::subscribe, "B");

    while (1)   
    {
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t result = zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));
        assert(result && "recv failed");

        std::cout << "Thread2: [" << recv_msgs[0].to_string() << "] "
            << recv_msgs[1].to_string() <<std::endl;
    }
    
}

void SubscriberThread2(zmq::context_t *ctx) {
    //  Prepare our context and subscriber
    zmq::socket_t subscriber(*ctx, zmq::socket_type::sub);
    subscriber.connect("inproc://#1");

    //  Thread3 opens ALL envelopes
    subscriber.set(zmq::sockopt::subscribe, "");

    while (1) {
        // Receive all parts of the message
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t result =
          zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));
        assert(result && "recv failed");

        std::cout << "Thread3: [" << recv_msgs[0].to_string() << "] "
                  << recv_msgs[1].to_string() << std::endl;
    }
}

int main()
{
    int a, b, c;
    std::tie(a, b, c) = zmq::version();

    cout << "version = "
         << a << b << c << endl;
    
    zmq::context_t ctx(0);

    auto thread1 = std::async(std::launch::async, PublisherThread, &ctx);

    // Give the publisher a chance to bind, since inproc requires it
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    auto thread2 = std::async(std::launch::async, SubscriberThread1, &ctx);
    auto thread3 = std::async(std::launch::async, SubscriberThread2, &ctx);
    thread1.wait();
    thread2.wait();
    thread3.wait();

}