CXX = arm-none-eabi-g++

CXXFLAGS += -std=c++20 -Og -nostdlib -nostdlib++ -ffreestanding -fno-exceptions -mcpu=cortex-m4 -Wall -Wextra -Werror -Iinclude -ffunction-sections
LDFLAGS += -mthumb -Tlinkerscript.ld

BUILDDIR = build
BIN = kernel

SRCS = $(shell find src -type f)
OBJS = $(SRCS:%=$(BUILDDIR)/%.o)

.PHONY: all clean

all: $(BIN)

$(BUILDDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(CXXFLAGS) $(LDFLAGS) $(OBJS)

clean:
	rm -rf $(BUILDDIR)/* $(BIN)
