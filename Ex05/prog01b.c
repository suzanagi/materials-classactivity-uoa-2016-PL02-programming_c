#include <stdio.h>

int main()
{
    int a[ ] = {12, 10, 4, 23, 2, -5 };
    int *ptr = a; 

    printf("*ptr=%d\n",*ptr);//0番目の要素(12)が出力される
    printf("*(ptr + 2)=%d\n",*(ptr + 2));//ポインタの指定により0+2番目の要素(4)が出力される
    printf("ptr[2]=%d\n",ptr[2]);//同上
    printf("ptr[2]++=%d\n",ptr[2]++);//インクリメントされるまえのptr[2]が出力される
    printf("*++ptr=%d\n",*++ptr);//インクリメントされてから出力されるからptr[2](10)
    printf("*ptr--=%d\n",*ptr--);//上の命令で使用したポインタにある10が出力される
    printf("*ptr=%d\n",*ptr);//指定されていないため0番目(12)を出力

    printf("a[0]=%d\n",a[0]);
    printf("a[1]=%d\n",a[1]);
    printf("a[2]=%d\n",a[2]);
    printf("a[3]=%d\n",a[3]);
    printf("a[4]=%d\n",a[4]);
    printf("a[5]=%d\n",a[5]);

    printf("a[]=%p\n",--ptr);

  return 0;
}
