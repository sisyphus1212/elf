;
; yasm -f bin rev_mach-o.asm
; it's tiny.asm from http://osxbook.com/blog/2009/03/15/crafting-a-tiny-mach-o-executable/
; with very few modifications in order to have both a valid and working hello-world mach-o
; 
; http://twitter.com/__rev
;

BITS 32
        org   0x1000

        db    0xce, 0xfa, 0xed, 0xfe       ; magic
        dd    7                            ; cputype (CPU_TYPE_X86)
        dd    3                            ; cpusubtype (CPU_SUBTYPE_I386_ALL)
        dd    2                            ; filetype (MH_EXECUTE)
        dd    2                            ; ncmds
        dd    _ep2 - _text                 ; cmdsize
        dd    0                            ; flags
_text:
        dd    1                            ; cmd (LC_SEGMENT)
        dd    56                           ; cmdsize | sizeof(segment_command) makes it valid
        db    "T"                          ; segname
        db    0                            ; segname padding
_ep:
        ; SYS_write
        push  msg_size                     ; this is part of segname padding
        push  msg
        push  ecx
        push  ebx
        int   0x80

        ; - SYS_exit
        push  ebx
        jmp   _ep2

        dd    0x1000                       ; vmaddr
        dd    0x1000                       ; vmsize
        dd    0                            ; fileoff
        dd    filesize                     ; filesize
        dd    7                            ; maxprot
        dd    5                            ; initprot
        dd    0                            ; nsects
        dd    0                            ; flags

        dd    5                            ; cmd (LC_UNIXTHREAD)
        dd    80                           ; cmdsize
        dd    1                            ; flavor (i386_THREAD_STATE)
        dd    16                           ; count (i386_THREAD_STATE_COUNT)
        dd    4, 0, 1, 0, 0, 0, 0, 0       ; state
        dd    0, 0, _ep, 0, 0, 0, 0, 0     ; state
_ep2:
        mov   eax, ecx
        int   0x80

filesize equ  $ - $$

msg db 'Hello world', 0ah
        msg_size equ $ - msg
