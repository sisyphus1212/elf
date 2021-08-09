
# Install and use darling in Ubuntu 16.04

首先到这里 https://github.com/darlinghq/darling/releases 下载两个 .deb 包：

    darling-dkms_0.1.20200331.testing_amd64.deb
    darling_0.1.20200331.testing_amd64.deb

下载完以后建议用 gdebi 来依次安装，这个可以自动解决和安装依赖。

    $ sudo apt-get install gdebi-core
    $ sudo gdebi darling-dkms_0.1.20200331.testing_amd64.deb
    $ sudo gdebi darling_0.1.20200331.testing_amd64.deb

接下来简单试试：

    $ darling shell
    Darling [/Volumes/SystemRoot/home/falcon]$ uname -a
    Darwin ubuntu 16.0.0 Darwin Kernel Version 16.0.0 x86_64
    Darling [/Volumes/SystemRoot/home/falcon]$ file /bin/bash 
    /bin/bash: Mach-O 64-bit executable x86_64
    Darling [/Volumes/SystemRoot/home/falcon]$ gcc --version
    Invoked with: /Library/Developer/DarlingCLT/usr/bin/xcrun gcc --version
    Executing /Library/Developer/DarlingCLT/usr/bin/gcc
    Failed to execute program /Library/Developer/DarlingCLT/usr/bin/gcc

发现自带的  gcc, clang 暂时都不能直接跑，还是需要安装 xcode，去官网下 xcode 吧（需要 Apple 帐号）。

  <https://xcodereleases.com/>

安装说明：

    $ cd /Applications
    $ unxip Xcode_11.3.xip


也可直接安装命令行开发工具：

    $ xcode-select --install


更多资料：

* <https://www.darlinghq.org/>
* <https://docs.darlinghq.org/index.html>
* <https://github.com/darlinghq>
* <https://github.com/darlinghq/darling/releases>
