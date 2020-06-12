/*
 * hw5-sorting.c
 *
 *  Created on: June 9, 2020
 *
 *  Homework 11: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE            13    /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a); //선택정렬
int insertionSort(int *a); //삽입정렬
int bubbleSort(int *a); //버블정렬
int shellSort(int *a); //쉘 정렬
/* recursive function으로 구현 */
int quickSort(int *a, int n); //퀵 정렬


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));

    printf("------- [2019038066] [Kimdoyeom] -------\n");

    do{
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array); //기본 배열 출력
            quickSort(array, MAX_ARRAY_SIZE); //퀵 정렬로 돌림
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

int initialize(int** a)
{
    int *temp = NULL;

    /* array가 NULL인 경우 메모리 할당 */
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else
        temp = *a;

    /* 랜덤값을 배열의 값으로 저장 */
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

int freeArray(int *a)
{
    // 비어 있지 않으면 메모리 할당을 취소시킴
    if(a != NULL)
        free(a);
    return 0;
}

void printArray(int *a)
{
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }
    for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열 순서를 출력
        printf("a[%02d] ", i);
    printf("\n");
    for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열값을 출력
        printf("%5d ", a[i]);
    printf("\n");
}

/*
선택정렬 가장 기본적인 정렬의 형태로 리스트에서 최소값을 찾아 맨 앞에 값과
변경하는 것을 반복한다.
*/
int selectionSort(int *a)
{
    int min; //최소값 저장 변수
    int minindex;//해당 최소값이 위치한 배열의 위치
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i;
        min = a[i];
        for(j = i+1; j < MAX_ARRAY_SIZE; j++) //j는 최소값 다음을 가리킴
        {
            if (min > a[j])//다음이 최소값보다 작으면
            {
                min = a[j]; //최소값을 j로 변경
                minindex = j; //위치도 변경한다.
            }
        }
        //반복이 끝나면 최종적으로 위치를 변경한다.
        a[minindex] = a[i]; 
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}

/*
삽입정렬 정렬된 부분과 그렇지 않은 공간을 나누어서 정렬되지 않은 공간의 값을 정렬된
공간에서 위치를 찾아 삽입하는 방식
*/
int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 1; i < MAX_ARRAY_SIZE; i++) //두 번째 값부터 실행
    {
        t = a[i];
        j = i;
        //기준이 되는 값 i가 이전 값보다 작게 된다면 반복문을 실행하여 
        //커질 때까지 계속 이전 값을 뒤로 이동시킴
        while (a[j-1] > t && j > 0)
        {
            a[j] = a[j-1];
            j--;
        }
        //반복이 종료되면 마지막 자리로 i의 값을 이동시킴 만약 다 정렬이 되어있다면
        //그냥 제자리 저장을 하는 용도로 쓰임
        a[j] = t;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}
/*
버블 정렬 인접한 두개의 수를 비교하여 큰 수를 앞으로 작은 수를 뒤로 이동시킴 
만약 자리 이동이 필요없다면 그대로 두고 다음으로 이동함 그래서 최종적으로 가장 큰
수가 제일 뒤로 이동하는 형태가 됨
*/
int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for(i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 크기만큼 반복을 돌림
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)
        {
            if (a[j-1] > a[j])//이전 값이 다음 값보다 크기가 큼 -> 자리 변경 필요
            {
                // 자리를 변경하는 코드 (swap같은 것)
                t = a[j-1];
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

/*
쉘 정렬 간격을 지정하여 그 간격만큼 떨어진 원소들의 크기를 비교하여 정렬시킴
해당 비교가 끝날 시 (초기 간격을 (배열 전체 크기)/2만큼으로 지정) 간격을 다시 1/2하여 해당 간격만큼 
원소를 비교하여 해당 간격이 1이 될때까지 반복 시킴.
*/
int shellSort(int *a)
{
    int i, j, k, h, v; //h는 간격을 의미

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //초기 간격은 배열 크기의 1/2 그리고 그 간격은 계속 1/2됨
    {
        for (i = 0; i < h; i++)
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];//간격 h에 있는 원소들을 저장
                k = j;//해당 간격의 대표 원소들의 순서를 저장
                while (k > h-1 && a[k-h] > v)//만약 두 간격 사이의 수를 비교하는 데 앞이 크다면 두 수를 변경
                {
                    a[k] = a[k-h]; //앞에 위치한 값을 뒤로 가져옴
                    k -= h;//간격들에 위치한 모든 수를 비교
                }
                a[k] = v; //만약 반복문이 실행되었다면 간격에서 자신보다 큰 수가 있던 위치로 이동
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}
/*
퀵 정렬 기준 값을 정하여 그것을 중심으로 왼쪽과 오른쪽의 집합을 나눈다. 
그리고 각각 정렬을 한다. 정렬이 끝나면 왼쪽 부터 다시 기준값을 정하여 
왼쪽과 오른쪽을 나눠 정렬을 하는 것을 반복한다.
*/
int quickSort(int *a, int n) // n은 배열의 크기
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n-1]; //기준값 여기서는 가장 오른쪽으로 잡음
        i = -1; //왼쪽 키값
        j = n - 1; //오른쪽 키값

        while(1)
        {
            while(a[++i] < v);// 왼쪽이 기준값보다 크기 전까지 증가 반복 -> i는 기준값보다 큰 수
            while(a[--j] > v);// 오른쪽이 기준값보다 작기 전까지 감소 반복 -> j는 기준값보다 작은 수

            if (i >= j) break; //왼쪽 값이 오른쪽 값보다 크면 종료
            //그게 아니라면 i와 j의 위치를 변경시켜준다.
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        //반복문을 빠져 나왔다는건 반복문 속 if문을 만족했기 때문으로
        //왼쪽이 기준값보다는 큰것이 되기에 기준값과 바꿔준다.
        t = a[i];
        a[i] = a[n-1];
        a[n-1] = t;
        
        //그리고 왼쪽의 마지막 위치로 기준값을 옮겨주었기에 배열의 크기로 왼쪽의 번호를 준다.
        quickSort(a, i); //왼쪽 분할
        quickSort(a+i+1, n-i-1); //오른쪽 분할
    }


    return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // MAX_HASH_TABLE_SIZE = 13이므로 key % 13의 값을 리턴
}

int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if(*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else {
        hashtable = *ht;    /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //각 테이블 값에 false값을 넣음
        hashtable[i] = -1;

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key); //hashcode를 key % 13의 값으로 저장
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1) //해당하는 헤쉬코드 테이블에 값이 없다면
        {
            hashtable[hashcode] = key; // 키값을 대입
        } else     { //그렇지 않다면 -> 충돌이 일어난다면

            index = hashcode; //hashcode 값을 index에 저장하고

            while(hashtable[index] != -1)// index값을 증가 시켜 빈공간을 찾아서 넣음 -> 배열을 순서대로 탐색함
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key; //빈 공간을 탐색 시 키값을 넣음
        }
    }

    return 0;
}

int search(int *ht, int key) //헤쉬 테이블에서 사용자가 입력한 키값에 해당하는 값을 출력
{
    int index = hashCode(key); //헤쉬 테이블에 키값을 key%13으로 저장했기에 해당 값을 인덱스에 넣음

    if(ht[index] == key) //만약 테이블 저장 과정에서 충돌이 일어나지 않았다면 해당 인덱스 값에 키값이 존재할 것
        return index; 

    while(ht[++index] != key) //그렇지 않고 충돌이 일어났다면 차례로 증가시켜 테이블을 탐색
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;
}
