[BITS 32]
[SECTION .text]
EXTERN code,bss,end,picreroute,kmain
mboot:
 dd 0x1BADB002
 dd 0x10001
 dd -(0x01BADB002+0x10001)
 dd mboot
 dd code
 dd bss
 dd end
 dd start
 
 dd 0
 dd 320
 dd 200
 dd 16

[GLOBAL start]
start:
 mov esp, stack+1024
 push eax
 push ebx
 mov ax, 0x10
 mov ds, ax
 mov es, ax
 mov fs, ax
 mov gs, ax
 call kmain
hlt

[GLOBAL gdt_flush]
gdt_flush:
 mov eax, [esp+4]
 lgdt [eax]
 mov ax, 0x10
 mov ds, ax
 mov es, ax
 mov fs, ax
 mov gs, ax
 mov ss, ax
 jmp 0x08:.flush
.flush:
ret

[GLOBAL idt_flush]
idt_flush:
 mov eax, [esp+4]
 lidt [eax]
ret

[GLOBAL read_cr0]
read_cr0:
	mov eax, cr0
retn

[GLOBAL write_cr0]
write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
retn

[GLOBAL read_cr3]
read_cr3:
	mov eax, cr3
retn

[GLOBAL write_cr3]
write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
retn

[SECTION .bss]
stack: resd 1024

[SECTION .data]

