#include <stdio.h>

void print1 (int *ptr, int rows);

int main(){
    int one[] = {0, 1, 2, 3, 4,};  
    printf("2019038066__kim do yeom\n");

    printf("one    =%p\n",one); //각각 주소들을 출력, one의 값도 주소와 같이 나옴
    printf("&one   =%p\n",&one); 
    printf("&one[] =%p\n",&one[0]); 
    printf("\n");

    print1(&one[0], 5);//각각 배열들이 int단위 이기에 4byte씩 차이가 나면서 출력이됨

    return 0;
}

void print1 (int *ptr, int rows) {    int i;
    printf("Address \t Contents\n"); 
    for (i = 0; i < rows; i++)
        printf("%p \t  %5d\n",ptr + i, *(ptr + i));  
    printf("\n");
}
