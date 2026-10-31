#include "Microcode.hpp"
#include <SpdrFirmware/Flag.hpp>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <format>

void Microcode::buildMicroInstruction(
    const Micro& instructions,
    std::uint32_t& output
) {
    output = 0;

    if (instructions.ioOperation) {
        output |= controlLines.getOutput(instructions.readFrom);
        output |= controlLines.getInput(instructions.writeTo);
    }

    for (auto& line : instructions.lines) {
        output |= controlLines.getLine(line);
    }
}

void Microcode::buildPath(
    const std::vector<Micro>& instruction,
    MicroInstructionPath& micro
) {
    for (std::size_t i = 0; i < maxMicrosCount; ++i) {
        if (i >= instruction.size()) {
            micro[i] = controlLines.getLine(Line::step_reset);
            continue;
        }
        buildMicroInstruction(instruction[i], micro[i]);
    }

}

void Microcode::buildMicrocode(
    const MicroSequence& instruction,
    MicrocodeInstruction& micro
) {
    for (auto flags : FlagSet::getAllCombinations()) {
        buildPath(instruction.micros.at(flags), micro[flags.intoInt()]);
    }
}

Microcode::Microcode() {
    for (auto& instruction : instructionSet.getInstructions()) {
        this->microcode.push_back({});
        auto& micro = this->microcode.back();
        buildMicrocode(instruction, micro);

        int minCycles = 0xff;
        int maxCycles = 0;
        for (auto& flagSet : FlagSet::getAllCombinations()) {
            int cycleCount = instruction.micros.at(flagSet).size();

            if (cycleCount < minCycles) {
                minCycles = cycleCount;
            }

            if (cycleCount > maxCycles) {
                maxCycles = cycleCount;
            }
        }

        std::cout << std::format("", instruction.opcode);

        std::stringstream ss{};
        instruction.instruction.print(ss, "val");

        std::cout << std::format("{:02x} {:16} {:2}", instruction.opcode, ss.str(), minCycles);

        if (minCycles != maxCycles) {
            std::cout << std::format("/{}", maxCycles);
        }
        std::cout << "\n";
    }
}

void Microcode::writeToFile(const std::string& prefix, int fileNumber) {
    std::stringstream fileName{};
    fileName << prefix << fileNumber << ".bin";

    std::ofstream file{fileName.str(), std::ios::binary};

    for (auto& instruction : this->microcode) {
        for (auto& instructionPath : instruction) {
            for (auto& micro : instructionPath) {
                std::uint8_t value = (micro >> (fileNumber * 8)) & 0xff;
                file << value;
            }
        }
    }

    file.close();
}

void Microcode::writeToFiles(const std::string& prefix) {
    for (int i = 0; i < 3; ++i)
        writeToFile(prefix, i);
}
