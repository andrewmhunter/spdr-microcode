#include "Microcode.hpp"
#include <iostream>
#include <filesystem>

int main() {
    Microcode microcode{};
    std::filesystem::create_directories("output");
    microcode.writeToFiles("output/micro");

    return 0;
}

