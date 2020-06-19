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
int front = -1;
int rear = -1;

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

/*너비 탐색 함수에서 사용하는 함수로 key값에 해당하는 vlist의 배열 번호를 반환하는 */
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
//그래프를 생성해주는 함수
int createGraph(Graph** First) {

    //그래프가 비어있지 않은 경우
    if (*First != NULL)
        destroyGraph(First);
    //그래프를 동적할당 해준다.
    *First = (Graph*)malloc(sizeof(Graph));
    //vlist를 미지 지정해둔 MAX_VERTEX만큼 동적할당 해준다.
    (*First)->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);
    //동적할당한 각 vlist의 head에 NULL값으로 초기화해준다.
    for (int i = 0; i < MAX_VERTEX; i++){
        (*First)->vlist[i].head = NULL;
    }

    return 0;
}

//생성된 그래프를 제거하는 함수
int destroyGraph(Graph** First) {

    //그래프가 생성되지 않았다면 종료
    if (First == NULL) {
        printf("The Graph already empty.");
        return 1;
    }
    //vlist에 연결된 vertex들을 삭제하는 과정
    for (int i = 0; i < MAX_VERTEX; i++){
        if ((*First)->vlist[i].head != NULL)
            deleteVertex(*First, (*First)->vlist[i].head->num);
    }
    //삭제 후 vlist를 해제하는 과정
    free((*First)->vlist);
    //vlist 삭제 후 그래프를 해제하는 과정
    free(*First);
    //그래프를 해제한 후 값을 NULL로 초기화
    *First = NULL;

    return 0;
}

//사용자가 입력한 키값을 vlist에 저장하는 함수
int insertVertex(Graph* First, int key) {

    //만약 그래프가 생성되지 않았다면 종료
    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    //새로운 값을 받는 vertex 메모리 할당
    Vertex* newvertex = (Vertex*)malloc(sizeof(Vertex));

    //할당된 vertex에 값을 넣음
    newvertex->num = key;
    newvertex->link = NULL;

    
    int i = 0;
    //빈 vlist공간을 찾음
    while (i != MAX_VERTEX) {
        
        if (First->vlist[i].head == NULL) break;
        i++;
    }
    //빈 vlist공간에 값을 넣음
    First->vlist[i].head = newvertex;

    return 0;
}

//사용자가 입력한 vertex를 삭제하는 함수
int deleteVertex(Graph* First, int key) {

    //그래프가 생성되지 않았다면 종료
    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    Vertex* head;
    int i = 0;
   //사용자가 입력한 vertex를 찾는 함수
    while (1){
	//해당 vlist값이 비어있지 않을때만 확인 함 -> nullptr오류 해결
        if (First->vlist[i].head != NULL) {
	    //해당 vertex가 key값이면 해당 vertex를 저장
            if (First->vlist[i].head->num == key) {
                head = First->vlist[i].head;
                break;
            }
        }

        i++;
	//만약 해당 vlist에 사용자가 입력한 키값이 없으면 에러 메시지 출력하고 종료
        if (i == MAX_VERTEX) {
            printf("There is no key you find...");
            return 1;
        }
    }

    //해당 vertex가 포함된 엣지들을 모두 삭제해야한다.
    int edgh[MAX_VERTEX] = {0}; //vertex와 연결된 엣지들을 저장하는 배열
    Vertex* next = head;
	
    //반복을 돌려 지우려고 하는 vertex에 연결된 엣지의 값을 배열에 저장한다.
    for (int k = 0; k < MAX_VERTEX; k++){

        if (next->link == NULL) break;
        next = next->link;
        edgh[k] = next->num;   
    }

    int j = 0;
    //해당 배열을 바탕으로 엣지를 제거하는 함수를 이용하여 모든 엣지를 삭제한다.
    while (edgh[j] != 0){
        deleteEdge(First, key, edgh[j]);
        j++;
    }
    //엣지가 모두 제거된 vertex를 삭제해준다.
    free(head);
    First->vlist[i].head = NULL;
    return 0;
}

//엣지를 추가하는 함수 두 개의 키값을 요구한다.
int insertEdge(Graph* First, int key1, int key2) {

    //그래프가 생성되지 않으면 종료
    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }
    //키값이 key1인 vertex
    Vertex* one;
    //키값이 key2인 vertex
    Vertex* two;
    
    //입력 키값에 해당하는 vertex를 저장해준다.
    for (int i = 0; i < MAX_VERTEX + 1; i++){
	//vlist에 찾는 키값이 없으면 종료
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
    key_1->link = NULL; //추가되는 엣지는 마지막에 저장되기 때문에

    //vertex를 이동시켜 마지막 vertex로 이동한다.
    Vertex* next1 = one;

    while (1){
	//마지막에 도착하면 엣지를 추가해준다.
        if (next1->link == NULL) {
            key_1->num = key2;
            next1->link = key_1;
            break;
        }
	//찾지 못하면 다음 vertex로 이동한다.
        next1 = next1->link;
    }

    /*key2값에 해당되는 vertex값에 key1 엣지 추가
    위의 것과 키값만 바뀜*/
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

//사용자가 입력한 두개의 vertex사이의 엣지를 제거하는 함수
int deleteEdge(Graph* First, int key1, int key2) {

    //그래프가 생성되지 않았으면 종료
    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }

    //key1값에 해당되는 vertex에 key2에 해당하는 엣지 값을 제거
    Vertex* post_1; //제거 이전 vertex
    Vertex* pre_1;  //제거 대상 vertex
    Vertex* next_1; //제거 앞 vertex

    for (int i = 0; i < MAX_VERTEX + 1; i++){
	//찾는 vertex가 없다면 종료
        if (i == MAX_VERTEX) {
            printf("There is no Key you find");
            return 1;
        }
	//첫번째 키값에 해당하는 vertex들을 저장함
        if (First->vlist[i].head->num == key1) {
            post_1 = First->vlist[i].head;
            pre_1 = post_1->link;
            next_1 = pre_1->link;
            break;
        }
    }
    //반복을 돌려서 제거 대상 vertex값이 키값과 같게 되게한다.
    while (pre_1 != NULL){
	// 찾으면 이전 vertex와 앞 vertex를 연결하고 해당 vertex를 제거한다.
        if (pre_1->num == key2) {
            post_1->link = next_1;
            pre_1->link = NULL;
            free(pre_1);
            break;
        }
	//그렇지 않으면 vertex를 이동시킨다.
        post_1 = pre_1;
        pre_1 = next_1;
        next_1 = next_1->link;
    }

    //key2값에 해당되는 vertex에 key1에 해당하는 엣지 값을 제거
    Vertex* post_2;
    Vertex* pre_2;
    Vertex* next_2;

    //앞선 방식과 동일하게 동작
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

//깊이 우선 탐색 - 스택을 사용하는 함수
int depthFS(Graph* First, int v) {

}

//너비 우선 탐색 - 큐를 사용하는 함수
int breadthFS(Graph* First, int v) {

    // 그래프가 생성되지 않았다면 종료
    if (First == NULL) {
        printf("The Graph is not created yet.");
        return 1;
    }
	
    //정점 vertex와 방문확인 배열을 만든다.
    Vertex* st;
    int visitflag[MAX_VERTEX] = { 0 };
    front = rear = -1; //초기화

    //첫번째 사용자가 지정한 정점의 vertex를 저장
    st = First->vlist[visit(First, v)].head;
    /*해당 vertex에 방문 표시함 visit함수는 v에 해당하는 
    값을 가진 vertex의 vlist에서의 순서 번호를 반환*/
    visitflag[visit(First, v)] = 1;
    //해당 값을 출력함
    printf("[ %d ]  ", v);
    //큐에 넣어 반복 시작을 
    enQueue(v);

    while (front != rear) {
        v = deQueue(); //정점에 해당하는 vertex를 큐에서 제거
        st = First->vlist[visit(First, v)].head;//제거된 vertex를 반복되는 vertex변수에 저장
        for (st; st; st = st->link) {
            if (!visitflag[visit(First, st->num)]) {//방문되지 않은 vertex라면
                printf("[ %d ]  ", st->num);//해당 값을 출력하고
                enQueue(st->num);//그 값을 큐에 넣어 다음 반복의 대상으로 준비
                visitflag[visit(First, st->num)] = 1;//방문 표시를 함
            }
        }
    }
    printf("\n");

    return 0;
}

//입력된 그래프를 출력하는 함수
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

/*
그래프는
Vertex head        edgh ~ ~
===================================
| vlist |  ->   | 엣지 vertex 값 |  -> ~ ~      
| vlist |  ->   | 엣지 vertex 값 |  -> ~ ~

와 같은 형식으로 출력됨*/


void enQueue(int item) {
    rear = (rear + 1) % MAX_VERTEX;//후미를 한칸 뒤로 옮긴 후
    queue[rear] = item;//해당 후미에 새로운 item값 저장
}

int deQueue() {
    front = (front + 1) % MAX_VERTEX;//있으면 front값을 한칸 뒤로
    return queue[front]; /*여기서 큐는 정말 삭제가 아니라 지정하는 이름만 옮기는 것이기에 위치만 반환해줌*/
}

int pop() {
	top--;
}

void push(int key) {
	printf("%d", key);
	stack[++top] = key;
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
