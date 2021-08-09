; yasm -f bin tiny_mfeiri.asm

BITS 32
        org   0x1000

        db    0xce, 0xfa, 0xed, 0xfe       ; magic
        dd    7                            ; cputype (CPU_TYPE_X86)
        dd    3                            ; cpusubtype (CPU_SUBTYPE_I386_ALL)
        dd    2                            ; filetype (MH_EXECUTE)
        dd    2                            ; ncmds
        dd    _end - _cmds               ; cmdsize
        dd    0                            ; flags
_cmds:
        dd    1                            ; cmd (LC_SEGMENT)
        dd    56                           ; cmdsize
        db    "__TEXT"                     ; segname

;        db    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ; segname


        db    0,0,0                        ; FILLER for yasm (3 bytes)
_start:
        push  byte 42                      ; 2 bytes
        sub   esp, 4                       ; 3 bytes (6 old nasm)
        int   0x80                         ; 2 bytes _exit(42)


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
        dd    1                            ; flavor (i386_THREAD_STATE)	    x86_THREAD_STATE32 see thread_status.h
        dd    16                           ; count (i386_THREAD_STATE_COUNT) x86_SAVED_STATE32_COUNT, see above



        dd    1, 0, 0, 0, 0, 0, 0, 0       ; state
        dd    0, 0, _start, 0, 0, 0, 0, 0  ; state



_end:

filesize equ  $ - $$


; 28 bytes header
; 56 bytes cmd LC_SEGMENT
; 80 bytes cmd LC_UNIXTHREAD
	; 16 bytes metadata
	; 64 bytes threadstate
; ---------
; 164 bytes total size