OUTPUT_FORMAT("elf32-i386")
ENTRY("start")
SECTIONS {
.text 0x100000 : {
code = . ; _code = . ;
*(.text)
}
.data : {
*(.data)
}
.bss : {
bss = . ; _bss = . ;
*(.bss)
*(.COMMON)
}
end = . ; _end = . ;
}
