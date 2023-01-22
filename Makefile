.DEFAULT_GOAL := run
all: clean
	mkdir build
	nasm -f bin ./boot.asm -o ./build/boot.bin
	#This is horrible, but tutorials gotta tutorial ig
	dd if=./message.txt >> ./build/boot.bin
	dd if=/dev/zero bs=512 count=1 >> ./build/boot.bin

run: all
	qemu-system-x86_64 -drive file=./build/boot.bin,format=raw

clean:
	rm -rf build
