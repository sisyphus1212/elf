
# C Standards

## 列出所有标准对应的版本号

    $ make stdc-version std

## 指定使用某个标准

    $ make stdc-version STD=c89

## 检查 GCC 版本

    $ make gcc-version

## 使用不同的函数调用规范，默认采用的是 cdecl

    $ make func-call
     objdump -d -j .text func-call | grep -B4 "call.*func"
     804845c:	83 ec 04             	sub    $0x4,%esp
     804845f:	6a 05                	push   $0x5
     8048461:	6a 03                	push   $0x3
     8048463:	6a 01                	push   $0x1
     8048465:	e8 98 ff ff ff       	call   8048402 <func>

    $ make clean
    $ make func-call CALL=fastcall
     8048468:	83 ec 0c             	sub    $0xc,%esp
     804846b:	6a 05                	push   $0x5
     804846d:	ba 03 00 00 00       	mov    $0x3,%edx
     8048472:	b9 01 00 00 00       	mov    $0x1,%ecx
     8048477:	e8 86 ff ff ff       	call   8048402 <func>

    $ make clean
    $ make func-call CALL=cdecl
     804845c:	83 ec 04             	sub    $0x4,%esp
     804845f:	6a 05                	push   $0x5
     8048461:	6a 03                	push   $0x3
     8048463:	6a 01                	push   $0x1
     8048465:	e8 98 ff ff ff       	call   8048402 <func>

    $ make compare

## 检查语法和标准偏离错误

   // 严格遵循某个标准，避免使用扩展特性

    $ make STD_ERROR=y STD=c89

   // 检查某个标准下，是否存在语法错误

    $ make OTHER_ERROR=y

    // 检查某个特性在所有版本下的工作情况下

    $ make std STD_ERROR=y
    $ make std OTHER_ERROR=y


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
