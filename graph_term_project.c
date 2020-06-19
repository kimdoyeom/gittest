#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20			// you can chage value 20

typedef struct Vertex {
	int num;					// vertex number
	struct Vertex* link;		//link to a next adjacent vertex
} Vertex;

typedef struct VertexHead {
	Vertex* head;				// linked list of all adjacent vertices
} VertexHead;

typedef struct Graph {
	VertexHead* vlist;			// list of all vertices: vlist[MAX_VERTEX]
} Graph;

//queue
int queue[MAX_VERTEX] = { 0 };
int front = 0;
int rear = 0;

//stack
int stack[MAX_VERTEX] = { 0 };
int top = -1;



/* 구현해야할 함수 목록*/
int createGraph(Graph** First); /* empty graph creation */
int destroyGraph(Graph** First); /* deallocating all allocated memory */
int insertVertex(Graph* First, int key); /* vertex insertion */
int deleteVertex(Graph* First, int key); /* vertex deletion */
int insertEdge(Graph* First, int key1, int key2); /* new edge creation between two vertices */
int deleteEdge(Graph* First, int key1, int key2); /* edge removal */
int depthFS(Graph* First, int key); /* depth firt search using stack || DFS pre-order 방식*/
int breadthFS(Graph* First, int key); /* breadth first search using queue || BFS level-order 방식*/
int printGraph(Graph* First); /* printing graph with vertices and edges || 각 노드간에 관계 즉 엣지 보여주기*/



//추가 구현 함수
void enQueue(int item);
int deQueue();

int pop();
void push(int key);

int visit(Graph* First, int key);


void main() {

    char command;
    int key, ekey;
    Graph* First;
    First = NULL;

    printf("======= [2019038066] [Kim Do Yeom] =======\n");
    do {
        printf("----------------------------------------------------------------\n");
        printf("                      Graph Linked  List                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Create Graph   = c           Destroy Graph   = g \n");
        printf(" Insert Vertex  = i           Delete Vertex   = d \n");
        printf(" Insert Edge    = n           Delete Edge     = e\n");
        printf(" depth FS       = f           breadth FS      = s\n");
        printf(" Print          = p           Quit            = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'c': case 'C':
            createGraph(&First);
            break;
        case 'g': case 'G':
            destroyGraph(&First);
            break;
        case 'i': case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertVertex(First, key);
            break;
        case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteVertex(First, key);
            break;
        case 'n': case 'N':
            printf("First Vertex Number = ");
            scanf("%d", &key);
            printf("Second Vertex Number = ");
            scanf("%d", &ekey);
            insertEdge(First, key, ekey);
            break;
        case 'e': case 'E':
            printf("First Vertex Number = ");
            scanf("%d", &key);
            printf("Second Vertex Number = ");
            scanf("%d", &ekey);
            deleteEdge(First, key, ekey);
            break;
        case 'f': case 'F':
            printf("Input your start node = ");
            scanf("%d", &key);
            depthFS(First, key);
            break;
        case 's': case 'S': 
            printf("Input your start node = ");
            scanf("%d", &key);
            breadthFS(First, key);
            break;
        case 'p': case 'P':
            printGraph(First);
            break;
        case 'q': case 'Q':
            printf("Terminate Progeram");
            break;
        default:
            printf("\n       >>>>>   Retry!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

}

int createGraph(Graph** First) {

    //그래프가 비어있지 않은 경우
    if (*First != NULL)
        destroyGraph(First);
    *First = (Graph*)malloc(sizeof(Graph));
    (*First)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);

    for (int i = 0; i < MAX_VERTEX; i++){
        (*First)->vlist[i].head = NULL;
    }

    return 0;
}

int destroyGraph(Graph** First) {

    if (First == NULL) {
        printf("The Graph already empty.");
        return 1;
    }

    for (int i = 0; i < MAX_VERTEX; i++){
        if ((*First)->vlist[i].head != NULL)
            deleteVertex(*First, (*First)->vlist[i].head->num);
    }

    free((*First)->vlist);
    free(*First);
    *First = NULL;

    return 0;
}

int insertVertex(Graph* First, int key) {

    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    Vertex* newvertex = (Vertex*)malloc(sizeof(Vertex));

    newvertex->num = key;
    newvertex->link = NULL;

    int i = 0;
    while (i != MAX_VERTEX) {
        
        if (First->vlist[i].head == NULL) break;
        i++;
    }

    First->vlist[i].head = newvertex;

    return 0;
}

int deleteVertex(Graph* First, int key) {

    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    Vertex* head;
    int i = 0;

    while (1){
        if (First->vlist[i].head != NULL) {
            if (First->vlist[i].head->num == key) {
                head = First->vlist[i].head;
                break;
            }
        }

        i++;

        if (i == MAX_VERTEX) {
            printf("There is no key you find...");
            return 1;
        }
    }

    //해당 vertex가 포함된 엣지들을 모두 삭제해야한다.
    int edgh[MAX_VERTEX] = {0};
    Vertex* next = head;

    for (int k = 0; k < MAX_VERTEX; k++){

        if (next->link == NULL) break;
        next = next->link;
        edgh[k] = next->num;   
    }

    int j = 0;

    while (edgh[j] != 0){
        deleteEdge(First, key, edgh[j]);
        j++;
    }

    free(head);
    First->vlist[i].head = NULL;
    return 0;
}

int insertEdge(Graph* First, int key1, int key2) {

    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    Vertex* one;
    Vertex* two;

    for (int i = 0; i < MAX_VERTEX + 1; i++){
        if (i == MAX_VERTEX) {
            printf("There is no Key you find");
            return 1;
        }

        if (First->vlist[i].head->num == key1) {
            one = First->vlist[i].head;
            break;
        }
    }

    for (int i = 0; i < MAX_VERTEX + 1; i++) {
        if (i == MAX_VERTEX) {
            printf("There is no Key you find");
            return 1;
        }

        if (First->vlist[i].head->num == key2) {
            two = First->vlist[i].head;
            break;
        }
    }

    //key1값에 해당되는 vertex값에 key2 엣지 추가
    Vertex* key_1=(Vertex*)malloc(sizeof(Vertex));
    key_1->link = NULL;

    Vertex* next1 = one;

    while (1){
        if (next1->link == NULL) {
            key_1->num = key2;
            next1->link = key_1;
            break;
        }
        next1 = next1->link;
    }

    //key2값에 해당되는 vertex값에 key1 엣지 추가
    Vertex* key_2 = (Vertex*)malloc(sizeof(Vertex));
    key_2->link = NULL;

    Vertex* next2 = two;

    while (1) {
        if (next2->link == NULL) {
            key_2->num = key1;
            next2->link = key_2;
            break;
        }
        next2 = next2->link;
    }

    return 0;
}

int deleteEdge(Graph* First, int key1, int key2) {

    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    //key1값에 해당되는 vertex에 key2에 해당하는 엣지 값을 제거
    Vertex* post_1;
    Vertex* pre_1;
    Vertex* next_1;

    for (int i = 0; i < MAX_VERTEX + 1; i++){
        if (i == MAX_VERTEX) {
            printf("There is no Key you find");
            return 1;
        }

        if (First->vlist[i].head->num == key1) {
            post_1 = First->vlist[i].head;
            pre_1 = post_1->link;
            next_1 = pre_1->link;
            break;
        }
    }

    while (pre_1 != NULL){
        if (pre_1->num == key2) {
            post_1->link = next_1;
            pre_1->link = NULL;
            free(pre_1);
            break;
        }
        post_1 = pre_1;
        pre_1 = next_1;
        next_1 = next_1->link;
    }

    //key2값에 해당되는 vertex에 key1에 해당하는 엣지 값을 제거
    Vertex* post_2;
    Vertex* pre_2;
    Vertex* next_2;

    for (int i = 0; i < MAX_VERTEX + 1; i++) {
        if (i == MAX_VERTEX) {
            printf("There is no Key you find");
            return 1;
        }

        if (First->vlist[i].head->num == key2) {
            post_2 = First->vlist[i].head;
            pre_2 = post_2->link;
            next_2 = pre_2->link;
            break;
        }
    }

    while (pre_2 != NULL) {
        if (pre_2->num == key1) {
            post_2->link = next_2;
            pre_2->link = NULL;
            free(pre_2);
            break;
        }
        post_2 = pre_2;
        pre_2 = next_2;
        next_2 = next_2->link;
    }

    return 0;
}


int depthFS(Graph* First, int v) {

}

//너비 우선 탐색
int breadthFS(Graph* First, int v) {

    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    Vertex* st;
    int visitflag[MAX_VERTEX] = { 0 };
    front = rear = -1;

    st = First->vlist[visit(First, v)].head;
    visitflag[visit(First, v)] = 1;
    printf("[ %d ]  ", v);
    enQueue(v);

    while (front != rear) {
        v = deQueue();
        st = First->vlist[visit(First, v)].head;
        for (st; st; st = st->link) {
            if (!visitflag[visit(First, st->num)]) {
                printf("[ %d ]  ", st->num);
                enQueue(st->num);
                visitflag[visit(First, st->num)] = 1;
            }
        }
    }
    printf("\n");

    return 0;
}

int printGraph(Graph* First) {

    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    Vertex* printv;

    printf("   Vertex head        edgh ~ ~\n");
    printf("===================================\n");
    for (int i = 0; i < MAX_VERTEX; i++){

        if (First->vlist[i].head != NULL){

            printv = First->vlist[i].head;
            printf("   ");
            for (int j = 0; j < MAX_VERTEX; j++){
                printf("| %d | -> ", printv->num);
                printv = printv->link;

                if (printv == NULL) {
                    printf("| NULL |\n");
                    break;
                }
            }
        }
    }
}


void enQueue(int item) {
    rear = (rear + 1) % MAX_VERTEX;//후미를 한칸 뒤로 옮긴 후
    queue[rear] = item;//해당 후미에 새로운 item값 저장
}

int deQueue() {
    front = (front + 1) % MAX_VERTEX;//있으면 front값을 한칸 뒤로
    return queue[front]; /*여기서 큐는 정말 삭제가 아니라 지정하는 이름만 옮기는 것이기에 위치만 반환해줌*/
}

int pop() {

}

void push(int key) {

}

//키값에 해당하는 그래프의 배열 번호를 반환
int visit(Graph* First, int key) {
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        if (First->vlist[i].head->num == key)
        {
            return i;
        }
    }
}
