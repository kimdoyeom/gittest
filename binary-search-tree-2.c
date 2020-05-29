#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);




int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */


/* you may add your own defined functions if necessary */
int isEmpty(); //큐가 비었는지 확인하는 함수
int isFull(); //큐가 꽉차있는지 확인
Node* searchIterative(Node* head, int key); //반복으로 키값 노드를 찾아 그 노드의 부모노드를 반환하는 함수
Node* superleft(Node* node); //입력한 노드 밑에 노드 중 가장 왼쪽 노드를 반환
Node* superright(Node* node); //입력한 노드 밑에 노드 중 가장 오른쪽 노드를 반환

int main()
{
	char command;
	int key;
	Node* head = NULL;
  printf("------- [2019038066]  [Kim Do Yeom] -------");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //스택를 사용하여
{
	while (1) {
		for (; node != NULL; node = node->left) //왼쪽 노드로 이동
			push(node);
		node = pop();

		if (!node) break;

		printf(" [%d] ", node->key);
		node = node->right;
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) return;
	enQueue(ptr);

	while (1)
	{
		ptr = deQueue();
		if (ptr) {
			printf(" [%d] ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

/*자식 노드가 있을경우 자식노드를 부모노드로 올림 자식이 2개 일때 왼쪽 노드의 가장 큰수를 올리거나 오른쪽 수의 가장 작은 노드를 올린다.
해당 자식 노드를 올리지 말고 그 해당 자식 노드를 찾은 후 부모 노드의 값을 그 값으로 바꾸고 해당 자식 노드를 free시킨다.

	   20				2
	 10					    8
	9  15			   5        17
	  12                   7       */

int deleteNode(Node* head, int key)
{
	int i = 0;
	Node* fl = (Node*)malloc(sizeof(Node));
	fl = head->left; // 루트 노드

	if ((head == NULL))
	{
		printf("Plz Initialize"); //아무것도 입력하지 않았을 때
		return 0;
	}
	if ((fl->key == key) && ((fl->left == NULL) && (fl->right == NULL))) // 루트 값이 키값이고 자식이 없을때
	{
		head->left = NULL;
		free(fl);

		return 1;
	}

	Node* p;
	Node* node;//키값 노드 저장할 노드

	p = searchIterative(head, key); //키값의 부모 노드를 받음

	if (!p) //찾는 키값이 없다면
	{
		printf("There is no Key you find");
		return 0;
	}

	// 키값 노드를 받음

	node = p->right;

	if (node == NULL || node->key != key)
	{
		node = p->left;
		i++;
	}


	/* 키값 노드의 왼쪽 노드가 없거나 리프노드 라면 */
	//오른쪽에서 가장 왼쪽을 받아옴
	if (node->left == NULL)
	{
		if (node->right != NULL) // 키값 노드 오른쪽에 자식이 있다면
		{
			Node* L; // 키값 노드의 가장 왼쪽 노드 받음
			Node* r; // L의 부모노드
			r = superleft(node);

			// 가장 왼쪽이 키값노드 오른쪽일 때
			if (r == NULL)
			{
				if (i == 0) p->right = node->right;
				if (i == 1) p->left = node->right;

				free(node);
				return 0;
			}

			L = r->left;

			node->key = L->key; //키값 노드값 삭제하고 L값을 이동

			//가장 왼쪽 노드에 오른쪽 자식이 있다면
			if (L->right != NULL)
			{
				Node* q = L->right;
				L = q;
				free(L); //원래 L자리를 초기화
				return 1;
			}


			r->left = NULL;
			free(L); //원래 L자리를 초기화
			return 1;
		}

		//리프 노드일 때
		if (i == 0) p->right = NULL; //키값을 초기화 시키고 부모노드의 값을 NULL로 변경
		if (i == 1) p->left = NULL;

		free(node); // 키값에 자식이 없음으로 바로 초기화

		return 0;
	}



	/*양쪽 노드가 다 있거나 왼쪽 노드만 있을 경우*/
	//왼쪽에서 가장 오른쪽 것을 받아옴
	if (node->left != NULL) // 키값 노드 왼쪽에 자식이 있다면
	{
		Node* R; //키값 노드 밑에서 가장 오른쪽 노드를 받아옴
		Node* r;
		r = superright(node); // R의 부모노드

		//가장 오른쪽이 키값노드 왼쪽일 때
		if (r == NULL)
		{
			Node* q = node->left;
			q->right = node->right;
			p->left = q;
			free(node);
			
			return 1;
		}

		R = r->right;// 키값 노드의 가장 오른쪽 노드 받음

		 // 가장 오른쪽 노드에 왼쪽 자식이 있다면
		if (R->left != NULL)
		{
			Node* q = R->left;
			r->right = q; //키값 노드를 삭제하고 R값을 이동
			node->key = R->key;
			free(R); //원래 R자리를 초기화
			return 1;
		}


		node->key = R->key; //키값 노드를 삭제하고 R값을 이동
		r->right = NULL;
		free(R); //원래 R자리를 초기화
		return 1;
	}
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	Node* x;
	if (top == -1)
		return '\0';
	else {
		x = stack[top--];
	}
	return x;
}

void push(Node* aNode)
{
	stack[++top] = aNode;
}



Node* deQueue()
{
	if (isEmpty(queue))//해당 큐가 비었으면
		return NULL;//오류값 전달, 비었는데 뭘 지워
	front = (front + 1) % MAX_QUEUE_SIZE;//있으면 front값을 한칸 뒤로
	return queue[front];/*여기서 큐는 정말 삭제가 아니라 지정하는 이름만
								옮기는 것이기에 위치만 반환해줌*/
}

void enQueue(Node* aNode)
{
	if (isFull(queue))//해당 큐가 가득 찼으면?
		return;//오류값 전달, 가득 찼는데 뭘 더 추가해?
	rear = (rear + 1) % MAX_QUEUE_SIZE;//후미를 한칸 뒤로 옮긴 후
	queue[rear] = aNode;//해당 후미에 새로운 item값 저장
}

int isEmpty()
{
	if (front == rear) /*원형큐이기 때문에 앞과 뒤가 같다면 비어있다.
								그런데 정말 그럴까라는 생각이 들었는데 원
								형큐는 공간 한개를 비워놓기 때문에 그리고 큐를
								지울때도 rear를 한칸 뒤로 옮기는 것이 규칙이기에
								front와 rear가 같지 않고선 큐가 빌 수 없다.*/
		return 1;//그러므로 참값을 반환
	return 0;
}

int isFull()
{
	if (front == (rear + 1) % MAX_QUEUE_SIZE)/*여기서는 모듈러 연산을 썼는데 의미는
												front 앞에 rear가 있다는 뜻인데 이
												역시 큐의 특성상 중간에 띄어질 이유가
												없기 때문에 앞선 말이 맞다면 해당 큐
												는 꽉 찬 것이다.*/
		return 1;// 그러므로 참!
	return 0;
}


Node* searchIterative(Node* head, int key)
{
	Node* p; //키값 노드의 부모노드를 저장하는 노드

	//헤더를 초기화 시키지 않았다면
	if (head == NULL) {
		printf("** ERROR ** you need to initialize the tree ");
		return 0;
	}

	p = head; //찾으려는 노드의 부모노드
	head = head->left;

	while (head) { //노드값이 눌이되면 반복 종료

		if (head->key == key) return p; //키값을 찾았으면 해당 노드의 부모노드 반환

		p = head; // 그렇지 않으면 헤더를 부모로

		if (head->key > key) head = head->left; //recursive와 동일한 형태
		else head = head->right;
	}

	return NULL;//못찾으면 눌 반환
}

//오른쪽 방향 탐색에서 쓰임
Node* superleft(Node* node) //입력한 노드 밑에 노드 중 가장 왼쪽 노드를 반환
{

	Node* p = node; //가장 왼쪽에 있는 노드의 부모 노드를 저장하는 노드
	node = node->right; //키값 노드의 오른쪽으로 이동

	if (node->left == NULL) return NULL; //가장 왼쪽이 키값노드 오른쪽일 때

	while (node->left)
	{
		p = node;
		node = node->left;
	}
	return p; //가장 왼쪽 노드의 부모 노드

}
//왼쪽 방향 노드에서 쓰임
Node* superright(Node* node) //입력한 노드 밑에 노드 중 가장 오른쪽 노드를 반환
{

	Node* p = node; //가장 왼쪽에 있는 노드를 저장하는 노드
	node = node->left; //키값 노드의 왼쪽으로 이동

	if (node->right == NULL) return NULL; //가장 오른쪽이 키값노드 왼쪽일 때

	while (node->right)
	{
		p = node;
		node = node->right;
	}
	return p;
}
