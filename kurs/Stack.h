#pragma once
struct Elem
{
	int number;
	int x;
	Elem* next;
};

struct Stack
{
	Elem* top;
};
void StackInit(Stack* s);
void StackDestroy(Stack* s);

int StackPush(Stack* s, int number, int x);
double StackPop(Stack* s);
int StackPeek(const Stack& s);
void StackClear(Stack* s);

bool StackIsEmpty(const Stack* s);
bool StackIsOrig(const Stack* s, int num);