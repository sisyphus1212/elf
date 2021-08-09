
# 通过 binfmt_misc 方式运行 C 语言

方法二：[binfmtc](https://www.netfort.gr.jp/~dancer/software/binfmtc.html.en)

## 下载、编译、安装 binfmtc

```
$ wget -c https://www.netfort.gr.jp/~dancer/software/downloads/binfmtc-0.9.tar.gz
$ tar binfmtc-0.9.tar.gz && cd binfmtc-0.9
$ ./configure && make && sudo make install
```

## 用扩展名注册 `.c` 自定义格式

```
$ sudo apt-get install binfmt-support
$ sudo update-binfmts --package binfmtc --install cscript \
  /usr/local/bin/binfmtc-interpreter --extension c
```

## 通过 binfmt_misc 方式运行 C 语言（Cont.）

### 用魔数注册自定义格式

```
$ echo -n '/*BINFMTC:' | hexdump -v -e '"\\""x"1/1 "%02x"' ; echo
\x2f\x2a\x42\x49\x4e\x46\x4d\x54\x43\x3a
$ sudo update-binfmts --package binfmtc --install cscript \
  /usr/local/bin/binfmtc-interpreter --magic '\x2f\x2a\x42\x49\x4e\x46\x4d\x54\x43\x3a'
```

### 通过 binfmt_misc 运行的 C 代码

```
/*BINFMTC:
*/
#include <stdio.h>

int main()
{
    printf("Hello World\n");
    return 0;
}
```

---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
