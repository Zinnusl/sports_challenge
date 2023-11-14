cmake_minimum_required(VERSION 3.5)

project (challenge)       

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(server server.cpp sportsdata/challenge.pb.cc positional_inaccuracy_generator.cpp sports_data_generator.cpp)
add_executable(client client.cpp sportsdata/challenge.pb.cc)

find_package(protobuf REQUIRED CONFIG)
find_package(cppzmq REQUIRED CONFIG)

target_link_libraries(client cppzmq)
target_link_libraries(client "protobuf::libprotobuf")

target_link_libraries(server cppzmq)
target_link_libraries(server "protobuf::libprotobuf")

