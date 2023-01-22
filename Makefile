.DEFAULT_GOAL := run
build_bootloader: clean
	mkdir build
	nasm -f bin boot.asm -o ./build/boot.bin

run: build_bootloader
	qemu-system-x86_64 -hda ./build/boot.bin

clean:
	rm -rf build

