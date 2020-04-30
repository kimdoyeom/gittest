/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);

int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    char command;
    int key;
    headNode* headnode = NULL;

    printf("------- [2019038066] [kimdoyeom] -------\n");


    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
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
            headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h) { //h는 현재 사용자가 지정한 노드의 첫번째를 지칭
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */
    listNode* p = h->first;//이중포인터를 사용하여 헤더노드를 복사

    listNode* prev = NULL; //첫번째노드를 옮길 노드 생성
    while (p != NULL) {
        prev = p; //지울 대상의 노드의 데이터를 복사
        p = p->link; //p가 가리키는 다음 노드를 복사
        free(prev);
    }
    free(h);
    return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;

    node->link = h->first;
    h->first = node;

    return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

    if ((h->first == NULL) || (h->first->key >= key)) {
        insertFirst(h, key);
    }

    else {
        listNode* curt = (listNode*)malloc(sizeof(listNode));
        listNode* prev = (listNode*)malloc(sizeof(listNode));
        prev = h->first;
        curt->key = key;

        while (1) {
            if (prev->link == NULL) {
                curt->link = prev->link;
                prev->link = curt;
                break;
            }
            else if (key <= prev->link->key) {
                curt->link = prev->link;
                prev->link = curt;
                break;
            }
            prev = prev->link;
        }
    }

    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    if ((h->first == NULL)) {
        insertFirst(h, key);
    }

    else {
        listNode* curt = (listNode*)malloc(sizeof(listNode));
        listNode* prev = (listNode*)malloc(sizeof(listNode));
        prev = h->first;
        curt->key = key;
        while (1) {
            if (prev->link == NULL) {
                curt->link = prev->link;
                prev->link = curt;
                break;
            }
            prev = prev->link;
        }
    }

    return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    listNode* p = (listNode*)malloc(sizeof(listNode));

    p = h->first;
    h->first = p->link;

    free(p);

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
    curt = prev->link;
    while (1) {
        if (key == h->first->key) {
            deleteFirst(h);
            break;
        }
        else if ((key == curt->key) && (curt->link == NULL)) {
            deleteLast(h);
            break;
        }
        else if (key == curt->key) {
            prev->link = curt->link;
            free(curt);
            break;
        }
        else if ((key != curt->key) && (curt->link == NULL)) {
            printf("The key doesn't exist in this list. plz reinput.\n");
            break;
        }
        prev = prev->link;
        curt = prev->link;

    }
    return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    listNode* curt = (listNode*)malloc(sizeof(listNode));
    listNode* prev = (listNode*)malloc(sizeof(listNode));
    prev = h->first;
    curt = prev->link;
    while (1) {
        if (curt->link == NULL) {
            prev->link = NULL;
            free(curt);
            break;
        }
        prev = prev->link;
        curt = prev->link;
    }
    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    headNode* lead = (headNode*)malloc(sizeof(headNode));
    headNode* mid = (headNode*)malloc(sizeof(headNode));
    headNode* trl = (headNode*)malloc(sizeof(headNode));

    lead->first = h->first;
    mid->first = NULL;

    while (lead->first) {
        trl->first = mid->first;
        mid->first = lead->first;
        lead->first = lead->first->link;
        mid->first->link = trl->first;
    }
    h->first = mid->first;
    return 0;
}


void printList(headNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT---\n");

    if (h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while (p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}
