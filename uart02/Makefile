
#ARMGNU ?= arm-none-eabi
ARMGNU ?= arm-linux-gnueabi

AARCH = -march=armv5t
AOPS = --warn --fatal-warnings $(AARCH)
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding $(AARCH)

notmain_world.bin :  strap.o notmain.o memmap
	$(ARMGNU)-ld strap.o notmain.o -T memmap -o notmain.elf
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy notmain.elf -O binary notmain.bin

strap.o : strap.s
	$(ARMGNU)-as $(AOPS) strap.s -o strap.o

notmain.o : notmain.c 
	$(ARMGNU)-gcc -c $(COPS) notmain.c -o notmain.o

clean :
	rm -f *.o
	rm -f *.elf
	rm -f *.bin
	rm -f *.list

