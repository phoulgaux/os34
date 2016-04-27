COMPOPTS = -c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -O0 -pipe -m32 -o
CC = gcc
CXX = g++

all: kernel drivers console cmds ui link

kernel:
	nasm start.asm -f elf32 -o out/start.o-asm
	nasm src/int/isr.asm -f elf32 -o out/isrs.o
	$(CC) kmain.c $(COMPOPTS) out/kmain.o
	$(CC) src/int/idt.c $(COMPOPTS) out/idt.o
	$(CC) src/int/isr.c $(COMPOPTS) out/isrc.o
	$(CC) src/int/irq3.c $(COMPOPTS) out/irq3.o
	$(CC) src/mem/gdt.c $(COMPOPTS) out/gdt.o
#	$(CC) src/mem/page.c $(COMPOPTS) out/page.o
#	$(CC) src/mem/mm.c $(COMPOPTS) out/mm.o
	$(CC) src/io.c $(COMPOPTS) out/io.o

drivers:
	$(CC) src/drv/vga.c $(COMPOPTS) out/vga.o
	$(CC) src/drv/kbd.c $(COMPOPTS) out/kbd.o
	$(CC) src/drv/pit.c $(COMPOPTS) out/pit.o
	$(CC) src/drv/rs232.c $(COMPOPTS) out/rs232.o
	$(CC) src/drv/floppy.c $(COMPOPTS) out/floppy.o

console:
	$(CC) src/con/con.c $(COMPOPTS) out/con.o
	$(CC) src/oslib/stdout.c $(COMPOPTS) out/stdout.o
	$(CC) src/oslib/string.c $(COMPOPTS) out/string.o

cmds:
	$(CC) src/cmds/ver.c $(COMPOPTS) out/cmd_ver.o
	$(CC) src/cmds/dbg.c $(COMPOPTS) out/cmd_dbg.o

ui:
	$(CC) src/ui/ui.c $(COMPOPTS) out/ui.o
	$(CC) src/ui/label.c $(COMPOPTS) out/label.o

link:
	ld -M="dbg/kernel.map" -Tkernel.ld  -o kernel.bin out/start.o-asm out/*.o

bochs:
	sudo mount ./floppy.img ./mount -o loop
	sudo cp kernel.bin ./mount
#	nautilus ./mount
#	sudo pico ./mount/grub/menu.lst
	sudo umount ./mount
	bochs

qemu:
	sudo mount ./floppy.img ./mount -o loop
	sudo cp kernel.bin ./mount
#	sudo pico ./mount/grub/menu.lst
#	sudo nautilus ./mount
	sudo umount ./mount
	qemu -serial /dev/stdout -fda floppy.img

objclean:
	rm out/*.o*

write:
	sudo dd if=floppy.img of=/dev/fd0 bs=512 count=2880

