
# Using upx

## 安装

    $ sudo apt-get install upx-ucl

## 压缩指定命令

    $ make
    cp /bin/ls .
    upx -qq `basename /bin/ls`
        126584 ->     57188   45.18%  linux/ElfAMD   ls

    $ make CMD=/bin/bash
    cp /bin/bash .
    upx -qq `basename /bin/bash`
       1037528 ->    469596   45.26%  linux/ElfAMD   bash
