.PHONY: all
all: sys

.PHONY: run
run: bochsrc sys
	bochs -qf bochsrc

a.img:
	rm -f a.img
# 	bximage -q -func=create -hd=16M $@ # For 8086/80286
	bximage -q -func=create -hd=4096M $@ # For IA-32


sys: a.img mbr.bin kernel.bin
	dd if=mbr.bin of=a.img conv=notrunc
	dd if=kernel.bin of=a.img bs=512 seek=1 conv=notrunc

mbr.bin: mbr.nas
	nasm mbr.nas -o mbr.bin

kernel.bin: kernel.nas
	nasm kernel.nas -o kernel.bin

.PHONY: clean
clean:
	-rm -f *.bin *.img
