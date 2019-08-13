#include "header.h"

Node *initNode(T data, Trie nod)
{
	Node *node;
	node = malloc(sizeof(struct node));
	node->data = data;
	node->nod = nod;
	node->next = NULL;
	return node;
}

Node *freeNode(Node *node)
{
	if (node) {
		free(node);
	}
	return NULL;
}

Queue initQueue(T data, Trie nod)
{
	Queue queue;

	queue = malloc(sizeof(struct queue));
	queue->head = queue->tail = initNode(data, nod);
	queue->size = 1;
	return queue;
}

Queue enqueue(Queue queue, T data, Trie nod)
{
	Node *node;

	if (isEmptyQueue(queue)) {
		if (queue == NULL)
			return initQueue(data, nod);
		free(queue);
		return initQueue(data, nod);
	}
	node = initNode(data, nod);
	queue->tail->next = node;
	queue->tail = node;
	queue->size++;
	return queue;
}

Queue dequeue(Queue queue)
{
	Node *tmp;

	if (!isEmptyQueue(queue)) {
		tmp = queue->head;
		queue->head = queue->head->next;
		tmp = freeNode(tmp);
		queue->size--;
	}
	return queue;
}

T first(Queue queue) {
	if (!isEmptyQueue(queue)) {
		return queue->head->data;
	} else {
		return -1;
	}
}

int isEmptyQueue(Queue queue) {
	if (queue == NULL || queue->head == NULL || queue->size == 0)
		return 1;
	return 0;
}

Queue freeQueue(Queue queue) {
	while (!isEmptyQueue(queue)) {
		queue = dequeue(queue);
	}
	if (queue)
		free(queue);
	return NULL;
}

void printQueue(Queue queue)
{
	int cont = queue->size;
	Node *temp = queue->head;
	while(cont > 0)
	{
		printf("%d ", temp->data);
		temp = temp->next;
		cont--;
	}
	printf("\n");

}


int compareQueue(Queue que1, Queue que2)
{
	if(que1 == NULL || que2 == NULL)
		return 0;

	if(que1->size != que2->size)
		return 0;

	Node *auxQue1 = que1->head;
	Node *auxQue2 = que2->head;

	int cont = que1->size;
	while(cont > 0)
	{
		if(auxQue2->data != auxQue1->data)
			return 0;
		cont--;
	}

	return 1;

}