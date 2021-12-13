#include <stdio.h>

// 变量声明
extern int a, b;
extern int c;
extern float f;

int func();


// 函数定义
int func()
{
    return 10;
}


int main ()
{
    /* 变量定义 */
    float a, b;
    float c;
    float f;

    /* 实际初始化 */
    a = 10;
    b = 20;

    c = a + b;
    printf("value of c : %f n", c);

    f = 70.0/3.0;
    printf("value of f : %f n", f);

    // 函数调用
    int i = func();
    printf("value of i : %f n", i);

    return 0;
}