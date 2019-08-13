typedef int T;

typedef struct node {
	T data;
	Trie nod;
	struct node *next;
}Node;

typedef struct queue {
	Node *head, *tail;
	int size;
}*Queue;

Queue initQueue(T data, Trie nod);
Node *initNode(T data, Trie nod);
Queue enqueue(Queue queue, T data, Trie nod);
Queue dequeue(Queue queue);
T first(Queue queue);
int isEmptyQueue(Queue queue);
Node *freeNode(Node *node);
Queue freeQueue(Queue queue);
void printQueue(Queue queue);
int compareQueue(Queue que1, Queue que2);
