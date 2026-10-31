#include "ControlLines.hpp"

const int ControlLines::aluStart{17};
const int ControlLines::inputDemuxes[] { 0, 3 };
const int ControlLines::outputDemuxes[] { 6, 9 };

ControlLines::ControlLines() {
    setLine(Line::nop, 0);

    setLineIndex(Line::step_reset, 12);
    setLineIndex(Line::set_flags, 13);
    setLineIndex(Line::halt, 14);
    setLineIndex(Line::counter_enable, 15);
    setLineIndex(Line::clear_irq, 23);

    setInputIndex(RID::PcH, 0, 1);
    setInputIndex(RID::MarL, 0, 2);
    setInputIndex(RID::Ins, 0, 3);
    setInputIndex(RID::Temp, 0, 4);
    setInputIndex(RID::A, 0, 5);
    setInputIndex(RID::Mem, 0, 6);
    setInputIndex(RID::Out, 0, 7);

    setInputIndex(RID::C, 1, 1);
    setInputIndex(RID::Sp, 1, 2);
    setInputIndex(RID::MarH, 1, 3);
    setInputIndex(RID::PcL, 1, 4);
    setInputIndex(RID::D, 1, 5);
    setInputIndex(RID::Lcd, 1, 6);
    setInput(RID::F, 7 << inputDemuxes[1] | getLine(Line::set_flags));
    setInput(RID::None, 0);

    setOutputIndex(RID::Mem, 0, 1);
    setOutputIndex(RID::Temp, 0, 2);
    setOutputIndex(RID::Alu, 0, 3);
    setOutputIndex(RID::PcH, 0, 4);
    setOutputIndex(RID::A, 0, 5);
    setOutputIndex(RID::C, 0, 6);
    setOutputIndex(RID::Sp, 0, 7);

    setOutputIndex(RID::Kbd, 1, 1);
    setOutputIndex(RID::PcL, 1, 2);
    setOutputIndex(RID::D, 1, 3);
    setOutputIndex(RID::F, 1, 4);
    setOutputIndex(RID::Prog, 1, 5);
    setOutput(RID::None, 0);

    setLineIndex(Line::carry, ControlLines::aluStart + 4);
    setLineIndex(Line::logic, 16);

    setAluLine(Line::inc, 0, false, true);
    setAluLine(Line::add, 9, false, false);
    setAluLine(Line::sub, 6, false, false);
    setAluLine(Line::passthrough, 0, false, false);
    setAluLine(Line::dec, 15, false, false);
    setAluLine(Line::sub_zero, 15, false, true);
    setAluLine(Line::lsh, 12, false, false);
    setAluLine(Line::b_and, 11, true, false);
    setAluLine(Line::b_or, 14, true, false);
    setAluLine(Line::b_xor, 6, true, false);
    setAluLine(Line::b_not, 0, true, false);
    setAluLine(Line::minus_one, 3, false, false);
    setAluLine(Line::zero, 3, false, true);

    setLineIndex(Line::flip, ControlLines::aluStart + 5);
    // set
}

std::uint32_t ControlLines::getLine(Line line) {
    return this->lines[line];
}

std::uint32_t ControlLines::getInput(RID reg) {
    return this->inputs[reg];
}
 
std::uint32_t ControlLines::getOutput(RID reg) {
    return this->outputs[reg];
}


void ControlLines::setLine(Line line, std::uint32_t value) {
    this->lines[line] = value;
}

void ControlLines::setLineIndex(Line line, std::uint32_t value) {
    setLine(line, 1 << value);
}

void ControlLines::setInput(RID reg, std::uint32_t value) {
    this->inputs[reg] = value;
}

void ControlLines::setOutput(RID reg, std::uint32_t value) {
    this->outputs[reg] = value;
}

void ControlLines::setInputIndex(RID reg, int demux, std::uint32_t value) {
    setInput(reg, value << ControlLines::inputDemuxes[demux]);
}

void ControlLines::setOutputIndex(RID reg, int demux, std::uint32_t value) {
    setOutput(reg, value << ControlLines::outputDemuxes[demux]);
}

void ControlLines::setAluLine(Line line, std::uint32_t value, bool logic, bool carry) {
    setLine(line, (value << ControlLines::aluStart) 
        | (logic ? getLine(Line::logic) : 0)
        | (carry ? getLine(Line::carry) : 0));
}
