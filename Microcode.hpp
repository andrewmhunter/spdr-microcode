#ifndef MICROCODE_HPP
#define MICROCODE_HPP

#include "ControlLines.hpp"
#include <SpdrFirmware/Flag.hpp>
#include <SpdrFirmware/InstructionSet.hpp>
#include <array>
#include <vector>
#include <string>

constexpr int maxMicrosCount{16};

using MicroInstructionPath = std::array<std::uint32_t, maxMicrosCount>;
using MicrocodeInstruction = std::array<MicroInstructionPath, 1 << flagCount>;

class Microcode {
private:

    InstructionSet instructionSet{};
    ControlLines controlLines{};
    std::vector<MicrocodeInstruction> microcode{};

    void buildMicroInstruction(
        const Micro& instructions,
        std::uint32_t& output
    );
    void buildPath(
        const std::vector<Micro>& instruction,
        MicroInstructionPath& micro
    );
    void buildMicrocode(
        const MicroSequence& instruction,
        MicrocodeInstruction& micro
    );
    void writeToFile(const std::string& prefix, int fileNumber);

public:
    Microcode();

    void writeToFiles(const std::string& prefix);
};

#endif

