#include <stdio.h>

struct student {
    char lastName[13];   /* 13 bytes */    
    int studentId;       /* 4 bytes  */
    short grade;         /* 2 bytes  */ //크게는 19byte가 될 수 있음

};

int main(){
    struct student pst;

    printf("2019038066__kim do yeom\n");

    printf("size of student = %ld\n", sizeof(struct student)); //struct 중요!!
    //근데 왜 24byte가 찍혔을까? lastname이 13인데 패딩을 통해 16byte 확보, studentId가 4byte, grade가 2byte를 차지하는데 여기서 또 패딩을 하여 4byte로 맞춤
    printf("size of int = %ld\n", sizeof(int));
    printf("size of short = %ld\n", sizeof(short)); //패딩을 채워넣기라고 함

    return 0;
} 