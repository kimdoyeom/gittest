#include <stdio.h>
#include <stdlib.h>

void main(){

    int list[5];
    int *plist[5]={NULL,0};//NULL로 초기화

    plist[0]=(int*)malloc(sizeof(int));//메모리를 할당 받아 주소를 넘겨줌

    list[0]=1;
    list[1]=100;

    *plist[0]=200;
    printf("2019038066__kim do yeom\n");

    printf("value of list[0] = %d\n", list[0]);//list[0]의 값 출력
    printf("address of list[0]      = %p\n", &list[0]);//주소 출력
    printf("value of list           = %p\n", list);//list[0]의 주소 출력
    printf("address of list (&list) = %p\n", &list);//list[0]의 주소 출력


    printf("-----------------------------------------\n\n");
    printf("value of list[1]   = %d\n", list[1]);
    printf("address of list[1] = %p\n", &list[1]);
    printf("value of *(list+1) = %d\n", *(list+1));//list[1] 값 출력, 1은 int값 만큼인 4byte가 더해진다. 그래서 list[1]을 의미하게된다.
    printf("address of list+1  = %p\n", list+1);
    
    printf("-----------------------------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]);
    printf("&plist[0]          = %p\n", &plist[0]);
    printf("&plist             = %p\n", &plist);//plist = plist[0] 으로 해석
    printf("plist              = %p\n", plist);//이것도 동일시 됨
    printf("plist[0]           = %p\n", plist[0]);//각각의 값에 저장된 주소
    printf("plist[1]           = %p\n", plist[1]);
    printf("plist[2]           = %p\n", plist[2]);
    printf("plist[3]           = %p\n", plist[3]);
    printf("plist[4]           = %p\n", plist[4]);//초기화 해주지 않아서 값이 없기에 주소가 없음

    free(plist[0]); //malloc으로 초기화시 마지막에 꼭 비워주는 작업을 해야함!!
}