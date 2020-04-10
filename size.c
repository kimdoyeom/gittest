#include<stdio.h>
#include<stdlib.h>

void main(){

    int **x;//이중 포인터를 선언한다

    printf("2019038066__kim do yeom\n");

    printf("sizeof(x) = %lu\n", sizeof(x)); 
    printf("sizeof(*x) = %lu\n", sizeof(*x)); //vscode의 경우 32bit체제여서 주소값이 4byte로 출력된다. 내 잘못이 아닌 것이다!!
    printf("sizeof(**x) = %lu\n", sizeof(**x)); //해당 값은 int를 기준으로 했기에 4byte가 출력된다.
}