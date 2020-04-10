#include <stdio.h>

struct student1 {  //구조체 선언
        char lastName;
        int studentId;
        char grade;
};  
typedef struct {
        char lastName;
        int studentId;
        char grade;
} student2;
int main(){
    struct student1 st1 = {'A', 100, 'A'}; //struct를 생략하고 출력시 구조체 오류가 발생한다. 즉, struct는 구조체이다. 

    printf("2019038066__kim do yeom\n");

    printf("st1.lastName = %c\n", st1.lastName); 
    printf("st1.studentId = %d\n", st1.studentId); 
    printf("st1.grade = %c\n", st1.grade); 

 
    student2 st2 = {'B', 200, 'B'}; //해당 문장은 왜 구조체가 없냐? 구조체 선언 당시 typedef를 붙이면 따로 자료형을 쓰지 않아도 된다.
 
    printf("\nst2.lastName = %c\n", st2.lastName); 
    printf("st2.studentId = %d\n", st2.studentId); 
    printf("st2.grade = %c\n", st2.grade); 


    student2 st3; 

    st3 = st2; //구조 치환, 이전에는 strcpy를 이용하여 여러모로 불편하게 바꿔야 했음.

    printf("\nst3.lastName = %c\n", st3.lastName); 
    printf("st3.studentId = %d\n", st3.studentId); 
    printf("st3.grade = %c\n", st3.grade); 

    /* equality test*/
    /* 
    if(st3 == st2) //이대로 했을때 오류가 발생, 비교를 위해선 각각의 내용을 비교해야됨
        printf("equal\n");
    else
        printf("not equal\n");
    */
return 0;
}
