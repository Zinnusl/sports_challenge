#include <iostream>
#include <string>
#include <zmq.hpp>
#include <zmq_addon.hpp>

#include "sportsdata/challenge.pb.h"

using std::cerr;
using std::cout;
using std::endl;

std::ostream& operator<<(std::ostream& os, const proto::Data3d& data) {
    os << "(" << data.x() << ", " << data.y() << ", " << data.z() << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const proto::Position& data) {
    os << "(" << data.sensorid() << ", " << data.timestamp_usec() << ", "
       << data.position() << ")";
    return os;
}

int main(int argc, char* argv[]) {
    zmq::context_t ctx;
    zmq::socket_t socket {ctx, zmq::socket_type::pull};
    socket.connect("tcp://localhost:36601");

    for (;;) {
        zmq::message_t reply {};
        zmq::recv_result_t recv_result =
            socket.recv(reply, zmq::recv_flags::none);

        if (!recv_result)
            continue;

        auto recv_pos = proto::Position {};
        recv_pos.ParseFromString(reply.to_string());
        std::cout << recv_pos << std::endl;
    }
    return 0;
}
