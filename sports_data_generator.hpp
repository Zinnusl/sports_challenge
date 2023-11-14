#pragma once

#include <array>
#include <random>
#include <vector>

#include "sportsdata/challenge.pb.h"

namespace sports_data_generator {
using RandomGenerator = std::default_random_engine;
using Output = std::vector<proto::Position>;

struct Player {
    unsigned long id = 0u;
    float x = 50.f;
    float y = 50.f;
    float z = 0.f;

    // Anmk.: Hier wuerde ich wahrscheinlich noch so etwas wie ein 5mps literal einbringen
    static constexpr float POSSIBLE_VELOCITY_HUMAN = 5.f;  //! Meter pro Sekunde
};

struct Field {
    std::array<Player, 10> players;

    static constexpr float min_x = 0.f;
    static constexpr float max_x = 100.f;

    static constexpr float min_y = 0.f;
    static constexpr float max_y = 100.f;

    bool is_valid_pos(float x, float y);
};

class SportsDataGenerator {
    RandomGenerator _gen;
    Field _field;

  public:
    explicit SportsDataGenerator();

    Output generate();
};

}  // namespace sports_data_generator
