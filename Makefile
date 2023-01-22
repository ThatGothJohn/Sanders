.DEFAULT_GOAL := run
all: clean
	mkdir build
	nasm -f bin ./boot.asm -o ./build/boot.bin

run: all
	qemu-system-x86_64 -drive file=./build/boot.bin,format=raw

clean:
	rm -rf build
