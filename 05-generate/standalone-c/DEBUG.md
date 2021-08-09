
# Debug with gdb

## 使用 gdb 分析动态链接过程：默认链接过程

    $ make DEBUG=y
    $ objdump -d hello
    Disassembly of section .plt:
    
    08048150 <_exit@plt-0x10>:
     8048150:	ff 35 bc 81 04 08    	pushl  0x80481bc
     8048156:	ff 25 c0 81 04 08    	jmp    *0x80481c0
     804815c:	00 00                	add    %al,(%eax)
    	...
    
    08048160 <_exit@plt>:
     8048160:	ff 25 c4 81 04 08    	jmp    *0x80481c4
     8048166:	68 00 00 00 00       	push   $0x0
     804816b:	e9 e0 ff ff ff       	jmp    8048150 <_exit@plt-0x10>
    
    08048170 <puts@plt>:
     8048170:	ff 25 c8 81 04 08    	jmp    *0x80481c8
     8048176:	68 08 00 00 00       	push   $0x8
     804817b:	e9 d0 ff ff ff       	jmp    8048150 <_exit@plt-0x10>
    
    Disassembly of section .text:
    
    08048180 <_start>:
     8048180:	55                   	push   %ebp
     8048181:	89 e5                	mov    %esp,%ebp
     8048183:	68 94 81 04 08       	push   $0x8048194
     8048188:	e8 e3 ff ff ff       	call   8048170 <puts@plt>
     804818d:	6a 00                	push   $0x0
     804818f:	e8 cc ff ff ff       	call   8048160 <_exit@plt>


    $ echo "add-auto-load-safe-path .gdbinit" ~/.gdbinit
    $ gdb ./hello 
    $ LD_BIND_NOW=1 gdb ./hello 
