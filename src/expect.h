#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <source_location>

namespace jvl
{
    // TODO: investigate why current() is for expect on Intel macs
    void expect(bool condition, std::source_location location = std::source_location::current()) {
        if (condition == false) {
            std::cerr << std::format("Unexpected: {} ({}, {})\n", "message", location.file_name(), location.line());
            std::abort();
        }
    }
}
