TARGET := microcode
SRCS := main.cpp Microcode.cpp ControlLines.cpp

BUILD_DIR := build
OBJECTS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJECTS:.o=.d)

CXXFLAGS := -std=c++20 -g -c -MD -MP -Wall -pedantic
LDFLAGS := -lspdr-firmware

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)

