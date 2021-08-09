/* Author: Wu Zhangjin, Wechat: tinylab */

#include <stdio.h>

__attribute__((weak)) char *hello = "hello";

__attribute__((weak)) void print(char *str)
{
  printf("%s\n", str);
}
