
# Data Alignment

## 案例分析

### Simple

    $ make list
    Default:

    make -s
    sizeof struct test is 4
    sizeof struct t[2] is 8
    pahole -C test test
    struct test {
    	char                       a;                    /*     0     1 */

    	/* XXX 1 byte hole, try to pack */

    	short int                  b;                    /*     2     2 */

    	/* size: 4, cachelines: 1, members: 2 */
    	/* sum members: 3, holes: 1, sum holes: 1 */
    	/* last cacheline: 4 bytes */
    };

    Packed:

    make -s PACKED=y
    sizeof struct test is 3
    sizeof struct t[2] is 6
    pahole -C test test
    struct test {
    	char                       a;                    /*     0     1 */
    	short int                  b;                    /*     1     2 */

    	/* size: 3, cachelines: 1, members: 2 */
    	/* last cacheline: 3 bytes */
    };

    Padded:

    make -s PADDED=y
    sizeof struct test is 4
    sizeof struct t[2] is 8
    pahole -C test test
    struct test {
    	char                       a;                    /*     0     1 */
    	char                       padding;              /*     1     1 */
    	short int                  b;                    /*     2     2 */

    	/* size: 4, cachelines: 1, members: 3 */
    	/* last cacheline: 4 bytes */
    };

### Complex

    $ make complex

注：可以结合 perf 工具统计 `perf list` 中列出来的：

    alignment-faults                                   [Software event]

参考资料：

* [Data alignment(数据、内存对齐)漫谈](https://blog.csdn.net/maxlovezyy/article/details/70231804)


---
Copyright Reserved, Author: Wu Zhangjin, Wechat: tinylab
<http://tinylab.org/360-elf>
