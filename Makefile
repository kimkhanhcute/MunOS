CXX = g++
ASM = nasm

CXXFLAGS = -ffreestanding -m32 -nostdlib -fno-exceptions -fno-rtti
LDFLAGS = -m elf_i386 -T linker.ld

all: kernel.bin iso

boot.o:
	$(ASM) -f elf32 kernel/boot.asm -o boot.o

kernel.o:
	$(CXX) $(CXXFLAGS) -c kernel/kernel.cpp -o kernel.o

vga.o:
	$(CXX) $(CXXFLAGS) -c kernel/vga.cpp -o vga.o

io.o:
	$(CXX) $(CXXFLAGS) -c kernel/io.cpp -o io.o

keyboard.o:
	$(CXX) $(CXXFLAGS) -c kernel/keyboard.cpp -o keyboard.o

string.o:
	$(CXX) $(CXXFLAGS) -c kernel/string.cpp -o string.o

rtc.o:
	$(CXX) $(CXXFLAGS) -c kernel/rtc.cpp -o rtc.o

idt.o: kernel/idt.cpp
	g++ -m32 -ffreestanding -c kernel/idt.cpp -o idt.o

isr.o: kernel/isr.asm
	nasm -f elf32 kernel/isr.asm -o isr.o

irq.o: kernel/irq.cpp
	g++ -m32 -ffreestanding -c kernel/irq.cpp -o irq.o

fs.o:
	g++ -m32 -ffreestanding -c kernel/fs.cpp -o fs.o

speaker.o:
	g++ -m32 -ffreestanding -c kernel/speaker.cpp -o speaker.o
	
command.o:
	g++ -m32 -ffreestanding -c kernel/command.cpp -o command.o

memory.o:
	g++ -m32 -ffreestanding -c kernel/memory.cpp -o memory.o

panic.o:
	g++ -m32 -ffreestanding -c kernel/panic.cpp -o panic.o

cpu.o:
	g++ -m32 -ffreestanding -c kernel/cpu.cpp -o cpu.o

kernel.bin: boot.o kernel.o vga.o io.o keyboard.o string.o rtc.o idt.o isr.o irq.o fs.o command.o memory.o panic.o cpu.o speaker.o
	ld $(LDFLAGS) boot.o kernel.o vga.o io.o keyboard.o string.o rtc.o idt.o isr.o irq.o fs.o command.o memory.o panic.o cpu.o speaker.o -o kernel.bin

iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp boot/grub/grub.cfg iso/boot/grub/
	grub-mkrescue -o MunOS.iso iso

run:
	qemu-system-x86_64 -cdrom MunOS.iso

clean:
	rm -rf *.o kernel.bin iso MunOS.iso

github:
	@read -p "Commit message: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push

test:
	make clean && make && make run

key:
	@if [ ! -f ~/.ssh/id_ed25519 ]; then \
		echo "Generating SSH key..."; \
		ssh-keygen -t ed25519 -C "$(USER)@MunOS" -N "" -f ~/.ssh/id_ed25519; \
	fi
	@echo ""
	@echo "===== PUBLIC KEY ====="
	@cat ~/.ssh/id_ed25519.pub
