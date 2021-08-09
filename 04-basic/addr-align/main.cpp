#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <vector>

// 测试组的粒度
#define TEST_GROUPS   128
// 测试个数
long long len = TEST_GROUPS * 1024 * 1024L;

// 是否对齐：打开为不对齐
//#define NON_ALIGN

// 是否测试原子行为
//#define ATOMIC

// 以下3个宏为测试函数开关
#define BIG_PAGE_TEST

//#define SMALL_OBJ_TEST
//#define SMALL_OBJ_4K_TEST

struct A {
    char      ch[6];      /* 6 bytes */
    long long padding[7]; /* 56 bytes */
    long long ll;         /* 如果不对齐，则从62开始，非cache line友好。 */
#ifndef NON_ALIGN
};
#else
} __attribute__((packed));
#endif

struct LinkNode {
    LinkNode() {
        void *pa = nullptr;
        if (int ret = posix_memalign(&pa, 64, sizeof(A))) {
            std::cerr << "posix_memalign err = " << strerror(ret) << std::endl;
            exit(ret);
        }
        a = (A*)pa;
    }

    A        *a;
    LinkNode *next;
};

__time_t big_page_test(int step = 64 * 2);
__time_t small_obj_test();
__time_t small_obj_4k_test();
void pretty_print(std::string func_name, __time_t msecs);

int main() {
    std::string func_name;
    __time_t msecs;

#ifdef BIG_PAGE_TEST
    func_name = "big_page_test";
    msecs = big_page_test();
#endif

#ifdef SMALL_OBJ_TEST
    A a;
    A *pa = &a;
    std::cout << "pa = "         << pa         << std::endl;
    std::cout << "pa.ll = "      << &pa->ll    << std::endl;
    std::cout << "alignof(A) = " << alignof(A) << std::endl;
    std::cout << "sizeof(A) = "  << sizeof(A)  << std::endl;

    func_name = "small_obj_test";
    msecs = small_obj_test();
#endif

#ifdef SMALL_OBJ_4K_TEST
    A a;
    A *pa = &a;
    std::cout << "pa = "         << pa         << std::endl;
    std::cout << "pa.ll = "      << &pa->ll    << std::endl;
    std::cout << "alignof(A) = " << alignof(A) << std::endl;
    std::cout << "sizeof(A) = "  << sizeof(A)  << std::endl;

    func_name = "small_obj_4k_test";
    msecs = small_obj_4k_test();
#endif

    pretty_print(func_name, msecs);
    return 0;
}

/**
 * 几点说明：
 *   0. 以下均为单线程下的测试，如果换了多线程，可能差距会进一步拉大。
 *   1. 以下测试都使用了尽可能大的内存，尽力弱化L2 L3 cache的影响。
 *   2. big_page_test和small_obj_test都没有排除硬件预取的影响。
 *      small_obj_4k_test会排除硬件预取的影响(预取不会超过一个page cache，
 *      page cache大小是4k)。
 *   3. 每一个case都测试了5次取得均值(更好的方式应该是测试更多次并去掉最优和最劣的结果)。
 *   4. 每一个测试的结对值结果都是" [非对齐ms] vs [对齐ms] -> [非对齐ms] : [对齐ms] "。
 *   5. 测试机配置：
 *                - L1 32KB，L2 256KB，L3 8196KB，cache line 64bytes
 *                - memory 16GB
 *                - cpu cores 4(超线程8线程)，3.50GHz
 *                - kernel 3.19.0-84-generic
 */

/**
 * 测试大的内存页[TEST_GROUPS == 128]。
 * 注：
 *   1. 默认仅测试跨cache line边界的(步长step为两个cache line大小，我机器是64，读者自行掌握)。
 *   2. 读者可以自行把步长调整到8,即每次读取一个机器字(相信应该都是64位的吧)。
 *
 * 现象及解释：
 *   [普通读操作]
 *     case 1: 步长为128
 *       现象： 22 vs 13 -> 1.69。对不对齐性能比值差距很大，
 *             但是这种测试压力下绝对值差距不是很明显。
 *       解释： 因为首次读取cache中没有数据，需要加载cache line，
 *             对齐比不对齐少加载一个cache line(假如不考虑L1预取)。
 *     case 2: 步长为8
 *       现象： 60 vs 60 -> 1。对不对齐无感。
 *       解释： 对于long long这种8字节的小类型，cache line内的数据居多，跨cache line的很少。
 *             cpu大多数操作都命中cache line，而这么大数据量下，
 *             case 1中的cache line边缘访问占比较小了，性能损耗相对很难感知。
 *   [原子操作]
 *     case 1: 步长为128
 *       现象： 5721 vs 109 -> 52.97。对不对齐性能差别非常非常大。
 *       解释： 考虑到读写、cache一致性以及原子操作的“实时”性，另外这种不对齐的原子行为很有可能用了总线锁，差别比[普通读操作]大非常多。
 *     case 2: 步长为8
 *       现象： 10500 vs 700 -> 15。对不对齐性能差据非常大！
 *       解释： 同case 1。但由于步长小，有了比较多的cache命中，比值趋向柔和。
 * @return
 */
__time_t big_page_test(int step) {
    void *p = nullptr;
    size_t area_size = sizeof(long long) * (len + 1);
    if (int ret = posix_memalign(&p, 64, area_size)) {
        std::cerr << "posix_memalign err = " << strerror(ret) << std::endl;
        return 0;
    }

    auto pc = (volatile char*)(p);

// 此case会导致边界访问long long跨cache line
#ifdef NON_ALIGN
    pc += 62;
#else
    pc += 64;
#endif

    volatile unsigned long long tmp;
    struct timeval t_val_start;
    gettimeofday(&t_val_start, NULL);
    for (long long i = 0; i < area_size / step - 1; ++i) {
#ifdef ATOMIC
        __sync_fetch_and_add((unsigned long long*)pc, i);
#else
        tmp = *((unsigned long long*)pc);
#endif
        pc += step;
    }

    struct timeval t_val_end;
    gettimeofday(&t_val_end, NULL);
    auto secs = t_val_end.tv_sec - t_val_start.tv_sec;
    auto usecs = t_val_end.tv_usec - t_val_start.tv_usec;
    auto msecs = secs * 1000 + usecs / 1000;

    return msecs;
}

/**
 * 测试小的链表连接的内存对象[TEST_GROUPS == 32]。
 * 链表及其中的结构都按照64 cache line大小对齐，小步长。
 * 现象及解释：
 *   [普通读操作]
 *       现象： 835 vs 1275 -> 0.66。对齐反而比不对齐慢了很多。
 *       解释： 按照我的结构体大小来看，对不对齐都会占两个cache line，
 *             不对齐也不会省cache，为什么非原子操作不对齐反而会变快？
 *             [!猜测!]通过内存地址的观察，我发现步长都超过了100bytes，
 *             结果就是对齐每200多bytes左右才会miss一次cache line，
 *             而不对齐会连续miss cache line，会促进预取(偶尔一次cache miss很正常，比如使用了一个不常用的全局变量，只有连续cache miss几次才会可能触发预取，关于预取参考memory prefetch)。
 *             我们不要忽略了硬件预取的特性。硬件在获取数据的时候
 *             如果算法内判断可以预取优化，它就会预取之后可能用到的数据。
 *             -> small_obj_4k_test会验证这个猜测。
 *   [原子操作]
 *       现象： 27500 vs 1600 -> 17.19。差距非常大，并且和big_page_test的小步长结果很像。
 *       类似于big_page_test。此时预取的效果会被原子的负载抵消掉。
 * @return
 */
__time_t small_obj_test() {
    LinkNode *head = new LinkNode();
    head->a = nullptr;
    auto cur_pre_node = head;
    for (long long i = 0; i < len; ++i) {
        void *pln;
        if (int ret = posix_memalign(&pln, 64, sizeof(LinkNode))) {
            std::cerr << "posix_memalign err = " << strerror(ret) << std::endl;
            return 0;
        }

        auto ln = new(pln)LinkNode();
        cur_pre_node->next = ln;
        cur_pre_node = ln;
    }

    volatile unsigned long long tmp;
    struct timeval t_val_start;
    gettimeofday(&t_val_start, NULL);
    long long i;
    auto cur_node = head->next;
    for (i = 0; i < len; ++i) {
#ifdef ATOMIC
        __sync_fetch_and_add(&cur_node->a->ll, i);
#else
        tmp = *((volatile unsigned long long*)(&cur_node->a->ll));
#endif
        cur_node = cur_node->next;
    }

    struct timeval t_val_end;
    gettimeofday(&t_val_end, NULL);
    auto secs = t_val_end.tv_sec - t_val_start.tv_sec;
    auto usecs = t_val_end.tv_usec - t_val_start.tv_usec;
    auto msecs = secs * 1000 + usecs / 1000;
    return msecs;
}

/**
 * 测试小的链表连接的内存对象[TEST_GROUPS == 32]。
 * 基本思想：硬件预取最多会预取一个page cache即4k内的数据，所以加入我的步长超过了4k，
 *          那么预取就没有效果了。
 *  [普通读操作]
 *       现象： 72 vs 55 -> 1.31。对不对齐有较大差距。
 *       解释： 步长跨4k排除预取干扰，对不对齐回归理论且差距很明显。
 *             有的可能会问了，那为什么big_page_test的小步长没出现small_obj_test
 *             的那种反常情况？因为big_page_test是long long型用的连续内存，不存在空隙，
 *             对不对齐都能很好的预测预取。
 * @return
 */
__time_t small_obj_4k_test() {
    std::vector<LinkNode*> page_head;
    page_head.reserve(512);
    LinkNode *head = new LinkNode();
    head->a = nullptr;
    auto cur_pre_node = head;
    LinkNode *last_4k_node;
    for (long long i = 0; i < len; ++i) {
        void *pln;
        if (int ret = posix_memalign(&pln, 64, sizeof(LinkNode))) {
            std::cerr << "posix_memalign err = " << strerror(ret) << std::endl;
            return 0;
        }

        auto ln = new(pln)LinkNode();
        if (0 == i) {
            last_4k_node = ln;
        } else if ((reinterpret_cast<long>(&ln->a->ll)
                    - reinterpret_cast<long>(&last_4k_node->a->ll))
                     > 1024 * 4) {
            page_head.push_back(ln);
            last_4k_node = ln;
        }

        cur_pre_node->next = ln;
        cur_pre_node = ln;
    }

    volatile unsigned long long tmp;
    struct timeval t_val_start;
    gettimeofday(&t_val_start, NULL);
    for (auto p : page_head) {
        tmp = *((volatile unsigned long long*)(&p->a->ll));
    }
    struct timeval t_val_end;
    gettimeofday(&t_val_end, NULL);
    auto secs = t_val_end.tv_sec - t_val_start.tv_sec;
    auto usecs = t_val_end.tv_usec - t_val_start.tv_usec;
    auto msecs = secs * 1000 + usecs / 1000;
    return msecs;
}

void pretty_print(std::string func_name, __time_t msecs) {
    std::cout << func_name << " duration "
#ifdef NON_ALIGN
              << "[without align] attr "
#else
              << "[with align] attr "
#endif

#ifdef ATOMIC
              << "[with atomic] "
#else
              << "[without atomic] "
#endif
              << "is [" << msecs << "] milli seconds." << std::endl;
}
