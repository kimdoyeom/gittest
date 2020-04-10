#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5];
    int *plist[5];

    list[0]=10;
    list[1]=11;

  printf("2019038066__kim do yeom\n");

    plist[0]=(int*)malloc(sizeof(int));

    printf("list[0] \t= %d\n", list[0]);
    printf("address of list \t= %p\n", list);
    printf("address of list[0] \t= %p\n", &list[0]);
    printf("address of list + 0 \t= %p\n", list+0);
    printf("address of list + 1\t= %p\n", list+1);//8byte 이동
    printf("address of list + 2\t= %p\n", list+2);
    printf("address of list + 3 \t= %p\n", list+3);
    printf("address of list + 4\t= %p\n", list+4);
    printf("address of list[4] \t= %p\n", &list[4]);//위와 동일 32byte를 움직임

    free(plist[0]);
}