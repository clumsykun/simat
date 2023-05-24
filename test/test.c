#include<stdio.h>
#include<string.h>

int main()
{
    double arr[3][4] = { 0 };
    int col = (int)sizeof(*arr)/(int)sizeof(**arr);//先判断列数
    int row = (int)sizeof(arr)/col/ (int)sizeof(**arr);//通过列数判断行数

    double *p = arr;

    return 0;
}
