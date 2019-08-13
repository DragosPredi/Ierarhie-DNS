
typedef int E;

typedef struct stack {
	E data;
	struct stack *next;
}*Stack;

Stack initStack(E data);
Stack push(Stack s, E data);
Stack pop(Stack s);
E top(Stack s);
int isEmptyStack(Stack s);
Stack freeStack(Stack s);
