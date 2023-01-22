.DEFAULT_GOAL := all
all: clean
	mkdir build bin
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin

run: all
	qemu-system-x86_64 -drive file=./bin/boot.bin,format=raw

clean:
	rm -rf build bin
