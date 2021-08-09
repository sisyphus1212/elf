
# Running Windows PE

在 Linux 下，可以用 wine 模拟器来运行跨系统的可执行文件 Windows PE。

不过，官方的 Wine 问题不少，建议使用 Deepin 的版本，有同学帮忙移植到了 Ubuntu/Debian，可参考：

* [deepin-wine-ubuntu](https://github.com/wszqkzqk/deepin-wine-ubuntu)
* [2019年wine QQ最完美解决方案](https://www.lulinux.com/archives/1319)

在 Ubuntu 16.04 成功运行 QQ 并登陆，步骤如下。

## 安装 Deepin wine for ubuntu

    $ git clone https://gitee.com/wszqkzqk/deepin-wine-for-ubuntu.git
    $ cd deepin-wine-for-ubuntu
    $ sudo ./install.sh

## 安装 QQ

    $ wget -c https://mirrors.aliyun.com/deepin/pool/non-free/d/deepin.com.qq.im.light/deepin.com.qq.im.light_7.9.14308deepin8_i386.deb
    $ sudo dpkg -i deepin.com.qq.im.light_7.9.14308deepin8_i386.deb

## 使用 QQ

在 Ubuntu 左侧搜索框搜索 QQ，点开图标后即可启动，用手机 QQ 扫码登陆即可。

这个图标实际上是一个快捷键，可以直接拖到桌面。其内容如下：

    #!/usr/bin/env xdg-open
    
    [Desktop Entry]
    Encoding=UTF-8
    Type=Application
    X-Created-By=Deepin WINE Team
    Categories=chat;
    Icon=deepin.com.qq.im
    Exec="/opt/deepinwine/apps/Deepin-QQ/run.sh" -u %u
    Name=QQ
    Name[zh_CN]=QQ
    Comment=Tencent QQ Client on Deepin Wine
    StartupWMClass=QQ.exe
    MimeType=

## 安装和使用 Windows 版本 GCC

如果想进一步研究 Windows PE，可以在 Windows 下使用 CygWin 或者 MinGW：

* [MinGW](http://mingw.org/), mingw-get-setup.exe
* [CygWin](http://www.cygwin.com/), setup-x86_64.exe 或 setup-x86.exe

MinGW 提供了一个轻量级的 Windows 本地 GCC 版本，而 CygWin 则提供了完整的 POSIX API 兼容的本地 GCC 版本。

在 Windows 下还可以结合 Git Bash 使用，进入到工作目录，右键执行 'Git Bash Here'：

* [Git for Windows 下载地址](https://git-scm.com/downloads)


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
