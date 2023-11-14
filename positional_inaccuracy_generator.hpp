#pragma once

#include <random>

#include "sportsdata/challenge.pb.h"

namespace positional_inaccuracy_generator {
using RandomGenerator = std::default_random_engine;
using Output = proto::Data3d;
using Input = proto::Data3d;

//! Ich gehe davon aus, dass die Ungenauigkeit das [0m, 100m] constraint fuer das Spielfeld ueberschreiten darf
class PositionalInaccuracyGenerator {
    RandomGenerator _gen;

  public:
    explicit PositionalInaccuracyGenerator();

    Output modify(const Input& data_in);
};

}  // namespace positional_inaccuracy_generator
