#include <stdio.h>

#define MAX_SIZE 100

float sum(float [], int);//sum 함수 선언
float input[MAX_SIZE],answer;
int i;//i를 전역변수로 설정해서 중복 선언을 막은듯
void main(){

    printf("2019038066__kim do yeom\n");
    for(i=0; i< MAX_SIZE; i++)
        input[1]=i;

    printf("address of input = %p\n", input);  //배열의 주소 출력
       
    answer = sum(input, MAX_SIZE); 
    printf("The sum is: %f\n", answer); 
}

float sum(float list[], int n){
    printf("value of list = %p\n", list);     
    printf("address of list = %p\n\n",&list); 
    
    int i;
   float tempsum = 0;//잠시 저장해둘 변수 선언
   for(i = 0; i <n; i++)
        tempsum += list[i];  
    return tempsum;//합을 리턴

}
    
