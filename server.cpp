#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>
#include <zmq.hpp>

#include "positional_inaccuracy_generator.hpp"
#include "sports_data_generator.hpp"

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    using namespace std::chrono_literals;

    zmq::context_t ctx;
    zmq::socket_t sock(ctx, zmq::socket_type::push);
    sock.bind("tcp://127.0.0.1:36601");

    auto data_gen = sports_data_generator::SportsDataGenerator {};
    auto inacc_gen =
        positional_inaccuracy_generator::PositionalInaccuracyGenerator {};

    for (;;) {
        auto generated_data = data_gen.generate();
        for (auto& generated_pos : generated_data) {
            *generated_pos.mutable_position() =
                inacc_gen.modify(generated_pos.position());

            const std::string data = generated_pos.SerializeAsString();
            sock.send(zmq::buffer(data), zmq::send_flags::none);
        }

        std::this_thread::sleep_for(1s);
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
