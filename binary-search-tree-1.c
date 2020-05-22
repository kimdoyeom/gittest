/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
//아무 노드를 삭제하는 것이 아닌 리프 노드를 삭제시키는 것임 즉, 리프 노드면 삭제 아니면 오류	
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
//빈노드가 아닐시 노드를 free시킴
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	
	printf("------- [2019038066] [kimdoyeom] -------");
	
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)
{
	//루트 노드가 없다면
	if (ptr == NULL) {
		printf("There is no Node...?");
		return 0;
	}

	Node* root = (Node*)malloc(sizeof(Node));
	root = ptr;

	if (root->left != NULL) inorderTraversal(root->left);
	printf(" [%d] ", root->key);
	if (root->right != NULL) inorderTraversal(root->right);

}

void preorderTraversal(Node* ptr)
{
	//루트 노드가 없다면
	if (ptr == NULL) {
		printf("There is no Node...?");
		return 0;
	}

	Node* root = (Node*)malloc(sizeof(Node));
	root = ptr;

	printf(" [%d] ", root->key);
	if (root->left != NULL) preorderTraversal(root->left);
	if (root->right != NULL) preorderTraversal(root->right);

}

void postorderTraversal(Node* ptr)
{
	//루트 노드가 없다면
	if (ptr == NULL) {
		printf("There is no Node...?");
		return 0;
	}

	Node* root = (Node*)malloc(sizeof(Node));
	root = ptr;

	if (root->left != NULL) postorderTraversal(root->left);
	if (root->right != NULL) postorderTraversal(root->right);
	printf(" [%d] ", root->key);
}


//루트보다 작으면 왼 크면 오른
int insert(Node* head, int key)
{
	
	Node* node = (Node*)malloc(sizeof(Node)); 
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	//헤더를 초기화 시키지 않았다면
	if (head == NULL) {
		printf("** ERROR ** you need to initialize the tree ");
		return 0;
	}
	//루트 노드가 없다면
	if (head->left == NULL) {
		head->left = node;
		return 1;
	} 
	
	//정상적인 방법
	if (head->left != NULL){

		Node* root = (Node*)malloc(sizeof(Node));
		root = head->left;

		/*노드의 키값을 입력 키값과 비교하여 키값이 크면 노드를
		오른쪽으로 키값이 작으면 노드를 왼쪽으로 옮긴다.
		만약 옮기려는 노드가 NULL이면 반복을 멈추고 나와서 키값을 비교한 후
		노드 키값보다 작으면 왼쪽에 크면 오른쪽에 저장시킨다.*/
		while (root != NULL) {

			if (root->key < key) {
				if (root->right == NULL) break;
				root = root->right;
			}
			if (root->key >= key) { //같을때는 왼쪽에 저장
				if (root->left == NULL) break;
				root = root->left;
			}		
		}

		if (root->key <= key) root->right = node;
		if (root->key >= key) root->left = node;
	}

	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	//헤더를 초기화 시키지 않았다면
	if (head == NULL) {
		printf("** ERROR ** you need to initialize the tree ");
		return 0;
	}
	//루트 노드가 없다면
	if (head->left == NULL) {
		printf("There is no Node...?");
		return 0;
	}

	Node* root = (Node*)malloc(sizeof(Node));
	Node* node = (Node*)malloc(sizeof(Node));
	root = head;
	node = head->left;

	while (node != NULL) //node가 눌이면 종료
	{
		if (node->key == key) { //키값을 찾음
			if ((node->left == NULL) && (node->right == NULL)) { //리프노드면
				if (root->key > key) {
					root->left = NULL;
					free(node);
					return 1;
				}
				if (root->key < key) {
					root->right = NULL;
					free(node);
					return 1;
				}
			}
			printf("This Key you fond is not Leaf Node"); //리프노드가 아님을 알림
			return 1;
		}

		root = node;

		if (node->key < key) node = node->right;
		if (node->key > key) node = node->left;
	}

	printf("There is no Key you find"); //찾는 키 없음

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) return NULL;//ptr이 눌일때 눌 리턴

	if (ptr->key == key) return ptr;//키값을 찾았을때 해당 주소 반환

	if (ptr->key > key) return searchRecursive(ptr->left, key); //키값이 작으면 왼쪽 노드로 이동
	return searchRecursive(ptr->right, key); //크면 오른쪽 노드로 이동
}

Node* searchIterative(Node* head, int key)
{
	//헤더를 초기화 시키지 않았다면
	if (head == NULL) {
		printf("** ERROR ** you need to initialize the tree ");
		return 0;
	}

	head = head->left;

	while (head) {//노드값이 눌이되면 반복 종료
		if (head->key == key) return head; //키값을 찾았으면 해당 노드 반환
		
		if (head->key > key) head = head->left; //recursive와 동일한 형태
		else head = head->right;
	}

	return NULL;//못찾으면 눌 반환
}


int freeBST(Node* head)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node = head;

	if (node->left != NULL) freeBST(head->left);
	if (node->right != NULL) {
		if(node->right != node) freeBST(head->right);
	}
	
	free(node);

	return 0;
}
