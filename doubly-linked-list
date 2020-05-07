/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;



typedef struct Head {
    struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
    char command;
    int key;
    headNode* headnode = NULL;

    printf("------- [2019038066] [kimdoyeom] -------");
    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Doubly Linked  List                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z':
            initialize(&headnode);
            break;
        case 'p': case 'P':
            printList(headnode);
            break;
        case 'i': case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e': case 'E':
            deleteLast(headnode);
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't': case 'T':
            deleteFirst(headnode);
            break;
        case 'r': case 'R':
            invertList(headnode);
            break;
        case 'q': case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}


int initialize(headNode** h) {
    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode* temp = (headNode*)malloc(sizeof(headNode)); 
    temp->first = NULL;
    *h = temp;

    return 1;
}

int freeList(headNode* h) {

    listNode* p = h->first; //포인터로 노드를 정의 후 헤더노드 복사

    listNode* prev = NULL; //첫번째 노드를 옮길 노드 생성

    while (p != NULL) {
        prev = p; //지울 대상의 노드의 데이터를 복사
        p = p->rlink; //p가 가리키는 다음 노드를 복사
        free(prev);
    }
    free(h);
    return 0;
}


void printList(headNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while (p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }

    printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    
    listNode* p = (listNode*)malloc(sizeof(listNode));
    listNode* curt = (listNode*)malloc(sizeof(listNode));
    p = h->first;
    curt->key = key;
    
    if (h->first == NULL) { //헤더노드 값이 삽입값보다 크거나 헤더노드에 아무것도 없을경우
        insertFirst(h, key);
    }

    else{

        while (p->rlink != NULL) {

            p = p->rlink;
        }
        p->rlink = curt;
        curt->llink = p;
        curt->rlink = NULL;
    }
    
    return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    if (h->first==NULL){
        return 0;
    }

    listNode* p = (listNode*)malloc(sizeof(listNode));
    p = h->first;

    while (p->rlink != NULL) {
        p = p->rlink;
    }
    p->llink->rlink = NULL;
    free(p);

    return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node;
    node->rlink = h->first;
    h->first = node;
    return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

    listNode* p = (listNode*)malloc(sizeof(listNode));

    p = h->first;
    h->first = p->rlink  ;

    free(p);

    return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* lead = (listNode*)malloc(sizeof(listNode));
    listNode* mid = (listNode*)malloc(sizeof(listNode));
    listNode* trl = (listNode*)malloc(sizeof(listNode));

    lead = h->first;
    mid = NULL;

    while (lead) {
        trl = mid;
        mid = lead;
        lead = lead->rlink;
        mid->llink = lead;
        mid->rlink = trl;
    }
    h->first = mid;
    mid->llink = mid;
    return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

    if ((h->first == NULL) || (h->first->key >= key)) { //헤더노드 값이 삽입값보다 크거나 헤더노드에 아무것도 없을경우
        insertFirst(h, key);
    }

    else {
        listNode* curt = (listNode*)malloc(sizeof(listNode));
        listNode* prev = (listNode*)malloc(sizeof(listNode));
        prev = h->first;
        prev->llink = prev;
        curt->key = key;

        while (1) {
            if (prev->rlink == NULL) { //헤더노드에만 값이 있는데 그 값이 삽입 값보다 작을 때 key값이 가장 클 경우
                curt->rlink = prev->rlink;
                prev->rlink = curt;
                curt->llink = prev;
                break;
            }
            else if (key <= prev->rlink->key) { //키값이 기준 노드의 다음 노드의 값보다 작다면 
                prev->rlink->llink = curt;      //prev 다음 노드의 llink를 삽입할려하는 노드로 지정한다.
                curt->rlink = prev->rlink;      //삽입 노드의 rlink를 prev다음 노드로 지정한다.
                prev->rlink = curt;             //prev의 rlink를 삽입노드로 지정한다.
                curt->llink = prev;             //curt의 llink를 prev로 지정한다. 
                break;
            }
            prev = prev->rlink;
        }
    }
    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    if (h->first->key == NULL) {
        printf("Noting in list. plz input key.\n");
        return 0;
    }
    listNode* curt = (listNode*)malloc(sizeof(listNode));
    listNode* prev = (listNode*)malloc(sizeof(listNode));
    prev = h->first;
    curt = prev->rlink;
    while (1) {
        if (key == h->first->key) {
            deleteFirst(h);
            break;
        }
        else if ((key == curt->key) && (curt->rlink == NULL)) {
            deleteLast(h);
            break;
        }
        else if (key == curt->key) {
            prev->rlink = curt->rlink;
            curt->rlink->llink = prev;
            free(curt);
            break;
        }
        else if ((key != curt->key) && (curt->rlink == NULL)) {
            printf("The key doesn't exist in this list. plz reinput.\n");
            break;
        }
        prev = prev->rlink;
        curt = prev->rlink;

    }
    return 1;
}
