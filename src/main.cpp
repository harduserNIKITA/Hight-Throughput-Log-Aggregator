#include <iostream>
#include <boost/asio.hpp>
#include <simdjson.h>

int main() {
    std::cout << "Log Aggregator starting..." << '\n';
    std::cout << "Simdjson version: " << SIMDJSON_VERSION << '\n';
    std::cout << "Boost version: " << BOOST_LIB_VERSION << '\n';
    return 0;
}
