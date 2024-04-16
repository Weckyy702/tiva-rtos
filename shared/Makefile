PREFIX = arm-none-eabi-

CXX = $(PREFIX)g++
OBJCOPY = $(PREFIX)objcopy
SIZE = $(PREFIX)size
GDB = $(PREFIX)gdb

STD ?= c++20
OPTFLAGS ?= -Os
DEBUGFLAGS ?= -ggdb
WFLAGS ?= -Wall -Wextra -Werror
CPUFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard
STDLIB = -nostdlib -nostdlib++
FFLAGS = -ffreestanding -fno-exceptions -ffunction-sections

CXXFLAGS += -std=$(STD) $(OPTFLAGS) $(DEBUGFLAGS) $(STDLIB) $(FFLAGS) $(CPUFLAGS) $(WFLAGS) -Iinclude 
LDFLAGS += $(CPUFLAGS) -Tlinkerscript.ld

BUILDDIR = build
BIN = $(BUILDDIR)/kernel
IMG = kernel.bin

SRCS = $(shell find src -type f)
OBJS = $(SRCS:%=$(BUILDDIR)/%.o)

.PHONY: clean img size upload openocd debug 

img: $(BIN)
	$(OBJCOPY) -Obinary $(BIN) $(IMG)

$(BUILDDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(CXXFLAGS) $(LDFLAGS) $(OBJS)

size: $(BIN)
	$(SIZE) --format=sysv $(BIN)

upload: img 
	lm4flash -v $(IMG)

openocd:
	openocd -f /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg&

debug: upload openocd
	$(GDB) -ex "tar ext :3333" $(BIN)

clean:
	rm -rf $(BUILDDIR)/* $(BIN) $(IMG)

