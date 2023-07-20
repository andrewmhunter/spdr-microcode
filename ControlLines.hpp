#ifndef CONTROLLINES_HPP
#define CONTROLLINES_HPP

#include <SpdrFirmware/Line.hpp>
#include <SpdrFirmware/Register.hpp>
#include <cstdint>
#include <map>

class ControlLines {
private:
    static const int aluStart;
    static const int inputDemuxes[];
    static const int outputDemuxes[];

    std::map<Line, std::uint32_t> lines{};
    std::map<RID, std::uint32_t> inputs{};
    std::map<RID, std::uint32_t> outputs{};

    void setLine(Line line, std::uint32_t value);
    void setLineIndex(Line line, std::uint32_t value);

    void setInput(RID reg, std::uint32_t value);
    void setOutput(RID reg, std::uint32_t value);

    void setInputIndex(RID reg, int demux, std::uint32_t value);
    void setOutputIndex(RID reg, int demux, std::uint32_t value);

    void setAluLine(Line line, std::uint32_t value, bool logic, bool carry);

public:
    std::uint32_t getLine(Line line);
    std::uint32_t getInput(RID reg);
    std::uint32_t getOutput(RID reg);

    ControlLines();
};

#endif

