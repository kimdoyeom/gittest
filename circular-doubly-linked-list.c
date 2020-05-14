/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); //초기화 함수
int freeList(listNode* h); // 동적 할당 취소 함수
int insertLast(listNode* h, int key); // 마지막 노드에 값을 넣음
int deleteLast(listNode* h); //마지막 노드의 값을 지움
int insertFirst(listNode* h, int key); //첫번째 노드에 값을 넣음
int deleteFirst(listNode* h); //첫번째 노드의 값을 지움
int invertList(listNode* h); // 리스트를 역순으로 재배열시킴

int insertNode(listNode* h, int key); // 키값 보다 큰 값 바로 앞에 넣음
int deleteNode(listNode* h, int key);// 키값과 동일 노드 지움

void printList(listNode* h); // 리스트를 출력함 



int main()
{
    char command;
    int key;
    listNode* headnode = NULL;

    printf("------- [2019038066] [kimdoyeom] -------");

    do {
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h; //r, l 링크 모두 순환이기에 자기 자신을 가리키게 된다
    (*h)->key = -9999; // 키값은... 그냥 넣은 것 같다
    return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

    if (h->rlink == h) { //리스트에 아무것도 없을 때
        free(h);
        return 0;
    }

    listNode* p = h->rlink; //헤더 노드 다음 노드를 받음

    listNode* prev = NULL; // 해제를 위한 노드 생성
    

    do { 
        prev = p; //첫번째 노드 복사
        p = p->rlink;// 다음 노드 저장
        free(prev); //메모리 해제 
    } while (p != h); //p가 헤더노드에 다다르면 종료

    free(h); //마지막으로 헤더 노드 해제

    return 0;
}



void printList(listNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if (h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while (p != NULL && p != h) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);


    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while (p != NULL && p != h) {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }

}



/**
 * list에 key에 대한 노드하나를 추가
 * list 마지막에 key에 대한 노드를 추가하는 것임
 */
int insertLast(listNode* h, int key) {
    if (h == NULL) {
        printf("you need initialize.\n");
        return 1;
    }

    if (h->rlink == h) {
        insertFirst(h, key);
        return 1;
    }

    listNode* p = (listNode*)malloc(sizeof(listNode));//헤더 노드를 복사
    listNode* prev = (listNode*)malloc(sizeof(listNode)); //키값을 가진 노드
    
    p = h;
    prev->key = key;

    /* 키값을 가진 노드를 헤더 앞 마지막 노드 뒤에 배치(비유적으로) */
    prev->llink = p->llink;
    prev->rlink = p;
    p->llink->rlink = prev;
    p->llink = prev;
    return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    if (h == NULL) { //초기화 안했을 때
        printf("you need initialize.\n");
        return 1;
    }

    if (h->rlink == h) { //초기화만 했을 때
        printf("Nothing in List. Plz insert something\n");
        return 1;
    }

    listNode* p = (listNode*)malloc(sizeof(listNode)); //헤더 노드 복사
    listNode* prev = (listNode*)malloc(sizeof(listNode)); //지울 노드

    p = h;
    prev = p->llink; //마지막 노드 복사

    if (p->rlink == prev) { //헤더 노드의 앞과 뒤 노드가 같다면 = 리스트가 1개일 때
        deleteFirst(h);
    }

    prev->llink->rlink = p; // 마지막 전 노드의 rlink를 헤더노드로 지정
    p->llink = prev->llink; // 헤더노드의 llink를 마지막 전 노드로 지정

    free(prev); // 마지막 노드 삭제

    return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    if (h == NULL) {
        printf("you need initialize.\n");
        return 1;
    }

    listNode* p = (listNode*)malloc(sizeof(listNode));
    listNode* prev = (listNode*)malloc(sizeof(listNode));

    p = h;
    prev->key = key;

    /* 키값을 가진 노드롤 헤더 노드 앞에 넣는다. */
    prev->llink = p;
    prev->rlink = p->rlink;
    p->rlink->llink = prev;
    p->rlink = prev;

    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

    if (h == NULL) {
        printf("you need initialize.\n");
        return 1;
    }

    if (h->rlink == h) {
        printf("Nothing in List. Plz insert something\n");
        return 1;
    }

    listNode* p = (listNode*)malloc(sizeof(listNode));
    listNode* prev = (listNode*)malloc(sizeof(listNode));
    
    p = h;
    prev = h->rlink;

    // 헤드 노드와 두번째 노드를 연결
    prev->rlink->llink = p;
    p->rlink = prev->rlink;

    //p를 메모리 해제
    free(prev);

    return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    if (h == NULL) {
        printf("you need initialize.\n");
        return 0;
    }

    if (h->rlink == h) {
        printf("Nothing in List. Plz insert something\n");
        return 0;
    }

    listNode* lead = (listNode*)malloc(sizeof(listNode));
    listNode* mid = (listNode*)malloc(sizeof(listNode));
    listNode* trl = (listNode*)malloc(sizeof(listNode));

    lead = h;
    mid = lead->llink;

    /* mid만 앞 뒤를 바꾸는 반복 */
    do{
        trl = mid;
        mid = lead;
        lead = lead->rlink;
        mid->llink = lead;
        mid->rlink = trl;
    } while (lead != h);

    return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
    if (h == NULL) {
        printf("you need initialize.\n");
        return 0;
    }

    if ((h->rlink == h)||(h->rlink->key >= key)){  //리스트에 아무것도 없거나 첫번째 노드값이 키값보다 클 경우
        insertFirst(h, key);
        return 0;
    }

     listNode* curt = (listNode*)malloc(sizeof(listNode));
     listNode* prev = (listNode*)malloc(sizeof(listNode));
     prev = h->rlink;
     curt->key = key;

     while (prev->rlink != h) {
           
        if (key <= prev->rlink->key){
           prev->rlink->llink = curt;      //prev 다음 노드의 llink를 curt로 지정한다.
           curt->rlink = prev->rlink;      //curt의 rlink를 prev다음 노드로 지정한다.
           prev->rlink = curt;             //prev의 rlink를 curt로 지정한다.
           curt->llink = prev;             //curt의 llink를 prev로 지정한다. 
           return 0;
        }
        prev = prev->rlink;
     }

     insertLast(h, key); //반복문을 빠져 나왔다는 것은 마지막 노드의 값이 키값보다 작다는 것이므로
        
    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    if (h == NULL) { //헤더에 아무것도 없을 때
        printf("Noting in list. plz input key.\n");
        return 0;
    }

    if (h->rlink == h) {
        printf("Nothing in List. Plz insert something\n");
        return 0;
    }

    listNode* curt = (listNode*)malloc(sizeof(listNode));
    listNode* prev = (listNode*)malloc(sizeof(listNode));
    prev = h->rlink;
    curt = prev->rlink; //해제할 노드

    while (curt != h) {
        //키값이 첫번째 노드의 키값과 동일할 때
        if (key == h->rlink->key) { 
            deleteFirst(h);
            return 0;
        }
        // 키값이 맨 마지막 노드일 때
        else if ((key == curt->key) && (curt->rlink == h)) {
            deleteLast(h);
            return 0;
        }
        // 키값을 찾았을 때
        else if (key == curt->key) {
            prev->rlink = curt->rlink;
            curt->rlink->llink = prev;
            free(curt);
            return 0;
        }
        
        prev = prev->rlink;
        curt = prev->rlink;

    }
    
    // 키값을 못찾았는데 순환이 끝났을 때
    printf("The key doesn't exist in this list. plz reinput.\n");

    return 0;
}
