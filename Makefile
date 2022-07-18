SRC = src
OBJ = obj
BIN = bin
ISO = iso

SRCS = $(wildcard $(SRC)/*.cc) $(wildcard $(SRC)/**/*.cc)
OBJS = $(patsubst $(SRC)/%,$(OBJ)/%,$(SRCS:.cc=.o))

OBJDIRS = $(dir $(OBJS))

KERNEL	= $(BIN)/kernel.elf
OSFILE	= $(BIN)/os.iso

# Compiler
CC				= clang++
CFLAGS			= -ggdb -Wall -Wextra -Wpedantic -pipe
INTERNALCFLAGS	= -I$(SRC) \
    -ffreestanding         \
    -fno-stack-protector   \
    -fno-stack-check       \
    -fno-pic               \
    -mabi=sysv             \
    -mno-3dnow             \
    -mno-red-zone          \
    -mcmodel=kernel        \
    -ggdb                  \
    -MMD

LD				= clang
INTERNALLDFLAGS	= \
    -nostdlib                   \
    -static                     \
    -Wl,-z,max-page-size=0x1000 \
    -Wl,-T,linker.ld            \
    -ggdb

.PHONY: all
all: $(SRC) $(OBJ) $(BIN) $(ISO) $(KERNEL)

$(OSFILE): $(KERNEL)
	cp -v $(KERNEL) limine.cfg $(ISO)/
	xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-cd-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        iso -o $@
	./limine/limine-deploy $@

qemu: $(OSFILE)
	qemu-system-x86_64 $(OSFILE) -m 1024 -s -S 

$(KERNEL): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

# $< is first in dependency list
# $@ is rule name
$(OBJ)/%.o: $(SRC)/%.cc
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ)
	mkdir $(OBJ)