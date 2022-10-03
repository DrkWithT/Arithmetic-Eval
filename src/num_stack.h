#ifndef NUM_STACK_H
#define NUM_STACK_H

#include <stdlib.h>

/*
	Declares a simple C object for a static stack implementation to store numbers.
	Used only for evalutaion of RPN.
*/

struct value_stack_obj
{
	int size;
	int top;
	float *data;
};

typedef struct value_stack_obj NumStack;

NumStack *Create_NumStack(int slots);

int Destroy_NumStack(NumStack *self);

int NumStack_isFull(const NumStack *self);

int NumStack_isEmpty(const NumStack *self);

float NumStack_peekTop(const NumStack *self);

int NumStack_pushItem(NumStack *self, float value);

float NumStack_popItem(NumStack *self);

#endif