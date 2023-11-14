#pragma once

#include <random>

#include "sportsdata/challenge.pb.h"

namespace positional_inaccuracy_generator {
using RandomGenerator = std::default_random_engine;
using Output = proto::Data3d;
using Input = proto::Data3d;

class PositionalInaccuracyGenerator {
    RandomGenerator _gen;

  public:
    explicit PositionalInaccuracyGenerator();

    Output modify(const Input& data_in);
};

}  // namespace positional_inaccuracy_generator
