/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node { // 노드
	int key;
	struct node *left;
	struct node *right;
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

void printStack();

int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n"); // 학번 이름 출력
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

		switch(command) {
		case 'z': case 'Z': // 메뉴 z : 초기화 함수 호출
			initializeBST(&head);
			break;
		case 'q': case 'Q': // 메뉴 q : 할당 해제 함수 호출 후 반복문 탈출
			freeBST(head);
			break;
		case 'i': case 'I': // 메뉴 i : 트리에 노드 삽입 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': // 메뉴 d : key 값에 대한 노드 삭제 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': // 메뉴 r : 순환 호출 함수 호출
			recursiveInorder(head->left);
			break;
		case 't': case 'T': // 메뉴 t : 반복 중위 함수 호출
			iterativeInorder(head->left);
			break;

		case 'l': case 'L': // 메뉴 l : 레벨 순회 함수 호출
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default: // 이외의 경우 : 에러 메시지
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q : 반복문 탈출

	return 1;
}

int initializeBST(Node** h) { // 초기화 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
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



void recursiveInorder(Node* ptr) // 순환 호출 중위 운행 함수
{
	if(ptr) {
		recursiveInorder(ptr->left); // left 노드 탐색
		printf(" [%d] ", ptr->key); // 노드 key 값 출력
		recursiveInorder(ptr->right); // right 노드 탐색
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // 반복 중위 운행 함수
{
	for(;;)
	{
		for(; node; node = node->left) // 반복하는 동안 현재 노드 left 노드로 변경
			push(node); // 현재 노드 스택에 push
		node = pop();

		if(!node) break; // NULL이면 반복문 탈출
		printf(" [%d] ", node->key); // 노드 key 값 출력

		node = node->right; // 노드를 현재노드의 right 노드로 변경
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 레벨 순회 함수
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr); // ptr을 큐에 삽입

	for(;;)
	{
		ptr = deQueue(); // 큐에서 ptr에 저장
		if(ptr) { // ptr이 NULL이 아니면
			printf(" [%d] ", ptr->key); // ptr key 값 출력

			if(ptr->left) // left 노드 존재하면
				enQueue(ptr->left); // left 노드 큐에 삽입
			if(ptr->right) // right 노드 존재하면
				enQueue(ptr->right); // right 노드 큐에 삽입
		}
		else
			break;

	}

}


int insert(Node* head, int key) // 노드 추가 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 할당
	newNode->key = key; // key 값 저장
	newNode->left = NULL; // 초기화
	newNode->right = NULL;

	if (head->left == NULL) { // NULL이면
		head->left = newNode; // newNode 저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // key 값이 더 큰 경우
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // key 값 보다 큰 경우
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) // key 값에 대한 노드 삭제 함수
{
	if (head == NULL) { // NULL이면 에러메시지
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // NULL이면 에러메시지
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;



	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {  // ptr이 NULL이 아니고 key 값이 다른 동안 반복
		if(ptr->key != key) {
			parent = ptr;	/* save the parent */

			if(ptr->key > key) // key 값 보다 크면
				ptr = ptr->left; // left 노드 저장
			else // key 값이 더 크면
				ptr = ptr->right; // right 노드 저장
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) // ptr이 NULL이면 에러 메시지
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) // 리프 노드일 때
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)
				parent->left = NULL; // 오른쪽에 NULL 저장
			else
				parent->right = NULL; // 왼쪽에 NULL 저장
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;

		}

		free(ptr); // 할당 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) // 자식 트리가 1개일 때
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left; // 왼쪽 저장
		else
			child = ptr->right; // 오른쪽 저장

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child; // 왼쪽에 child 저장
			else
				parent->right = child; // 오른쪽에 child 저장
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr); // 할당 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) // NULL이 아니면
	{
		parent = candidate; // parent에 candidate 저장
		candidate = candidate->left; // candidate 왼쪽 노드로 변경
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)
		parent->right = candidate->right; // parent의 오른쪽에 candidate의 오른쪽 노드 저장
	else
		parent->left = candidate->right; // parent의 왼쪽에 candidate의 오른쪽 노드 저장

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; // key 값 저장

	free(candidate); // 할당 해제
	return 1;
}


void freeNode(Node* ptr) // 메모리 할당 해제 함수
{
	if(ptr) {
		freeNode(ptr->left); // 후위 운행으로 할당 해제
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head) // 이진탐색 노드 할당 해제 함수
{

	if(head->left == head) // 트리에 노드가 없으면
	{
		free(head); // 헤드노드 해제 후 종료
		return 1;
	}

	Node* p = head->left; // p에 루트노드 저장

	freeNode(p); // freeNode 호출

	free(head); // 헤드노드 해제
	return 1;
}



Node* pop() // pop 함수
{
	if (top < 0) return NULL; // 원소가 없으면 NULL리턴
	return stack[top--]; // top 감소
}

void push(Node* aNode) // push 함수
{
	stack[++top] = aNode; // top 증가, aNode 저장
}

void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); 
	}
}

Node* deQueue() // 큐 원소 삭제 함수
{
	if (front == rear) { // 큐가 비어있을 때 에러 메시지
		//printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // (front + 1) / 최대 큐 사이즈의 나머지 값을 front에 저장
	return queue[front]; // 인덱스가 front인 큐 리턴

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; // (rear + 1) / 최대 큐 사이즈의 나머지 값을 rear에 저장
	if (front == rear) { // 큐가 꽉 찼을 때 에러메시지
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // 인덱스가 rear인 큐에 aNode 저장
}