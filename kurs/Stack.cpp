#include<iostream>
#include"Stack.h"

void StackInit(Stack* s)
{
	s->top = NULL;
}

void StackDestroy(Stack* s)
{
	StackClear(s);
}

int StackPush(Stack* s, int number, int x)
{
	Elem* elem = (Elem*)malloc(sizeof(Elem));
	if (!elem)
		return 0;
	elem->next = s->top;
	elem->number = number;
	elem->x = x;
	s->top = elem;
	return 1;
}

double StackPop(Stack* s)
{
	Elem* tmp;
	double value = DBL_MAX;

	if (s->top != NULL)
	{
		tmp = s->top;
		value = tmp->number;
		s->top = s->top->next;
		free(tmp);
	}
	return value;
}

double StackPeek(const Stack* s)
{
	if (s->top)
		return s->top->number;
}

void StackClear(Stack* s)
{
	while (!StackIsEmpty(s))
		StackPop(s);
}

bool StackIsEmpty(const Stack* s)
{
	return s->top == NULL;
}

bool StackIsOrig(const Stack* s, int num)
{
	for (Elem* elem = s->top; elem; elem = elem->next)
	{
		if (elem->number == num)
			return false;
	}
	return true;
}