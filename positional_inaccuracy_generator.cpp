#include "positional_inaccuracy_generator.hpp"

namespace positional_inaccuracy_generator {
PositionalInaccuracyGenerator::PositionalInaccuracyGenerator() {}

Output PositionalInaccuracyGenerator::modify(const Input& data_in) {
    // Ungenauigkeit in den Sensordaten respektiert nicht die Einschraenkungen des Field-struct.
    auto dist = std::uniform_real_distribution<float> {-0.3f, 0.3f};

    auto result = data_in;
    result.set_x(data_in.x() + dist(_gen));
    result.set_y(data_in.y() + dist(_gen));
    result.set_z(data_in.z() + dist(_gen));

    return result;
}
}  // namespace positional_inaccuracy_generator
