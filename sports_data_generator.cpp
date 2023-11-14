#include "sports_data_generator.hpp"

#include <iostream>
#include <random>

#include "sportsdata/challenge.pb.h"

namespace sports_data_generator {

SportsDataGenerator::SportsDataGenerator() {}

Output SportsDataGenerator::generate() {
    using namespace std::chrono;

    // Wir generieren 1x pro Sekunde Daten => Ein Spieler der sich im letzten Durchlauf
    // POSSIBLE_MANHATTEN_VELOCITY_HUMAN/2.f bewegt hat wuerde bei mehr als
    // POSSIBLE_MANHATTEN_VELOCITY_HUMAN/2.f als max Wert mglw. das Limit ueberschreiten.
    auto dist = std::uniform_real_distribution<float> {
        -Player::POSSIBLE_MANHATTEN_VELOCITY_HUMAN / 2.f,
        Player::POSSIBLE_MANHATTEN_VELOCITY_HUMAN / 2.f};

    // Zufaellige Bewegung der Spieler simulieren
    for (auto& player : _field.players) {
        float move_x = dist(_gen);
        float move_y = dist(_gen);

        if (_field.is_valid_pos(player.x + move_x, player.y + move_y)) {
            player.x += move_x;
            player.y += move_y;
        }
    }

    Output output;

    high_resolution_clock::time_point tp = high_resolution_clock::now();
    unsigned long sensor_id = 1u;
    for (const auto& player : _field.players) {
        auto position = proto::Position {};
        position.set_sensorid(sensor_id++);
        position.set_timestamp_usec(tp.time_since_epoch().count());
        auto data3d = new proto::Data3d {};
        data3d->set_x(player.x);
        data3d->set_y(player.y);
        data3d->set_z(player.z);
        position.set_allocated_position(data3d);  // Nimmt ownership
        output.push_back(position);
    }

    return output;
}

bool Field::is_valid_pos(float x, float y) {
    return min_x < x && x < max_x && min_y < y && y < max_y;
}
}  // namespace sports_data_generator
