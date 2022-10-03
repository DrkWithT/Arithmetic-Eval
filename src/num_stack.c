#include "num_stack.h"

NumStack *Create_NumStack(int slots)
{
	NumStack *new_num_stack = malloc(sizeof(NumStack));

	if (new_num_stack != NULL)
	{
		if (slots > 0)
			new_num_stack->size = slots;
		else
			new_num_stack->size = 10;

		new_num_stack->top = -1;
		new_num_stack->data = calloc(new_num_stack->size, sizeof(float));

		// check allocation before initializing data
		if (new_num_stack->data != NULL)
		{
			for(int i = 0; i < new_num_stack->size; i++)
				new_num_stack->data[i] = 0.0f; // zero all slots for safety
		}
		else
		{
			// dispose any badly allocated number stack
			free(new_num_stack);
			new_num_stack = NULL;
		}
	}

	return new_num_stack;
}

int Destroy_NumStack(NumStack *self)
{
	int can_free = self != NULL;

	if (can_free)
	{
		free(self->data);
		self->data = NULL;
		
		self->top = 0;
		self->size = 0;
	}
	
	return can_free;
}

int NumStack_isFull(const NumStack *self)
{
	return self->top >= self->size - 1;
}

int NumStack_isEmpty(const NumStack *self)
{
	return self->top <= -1;
}

float NumStack_peekTop(const NumStack *self)
{
	return self->data[self->top];
}

int NumStack_pushItem(NumStack *self, float value)
{
	int can_push = !NumStack_isFull(self);

	if (can_push)
	{
		self->top++;
		self->data[self->top] = value;
	}

	return can_push;
}

float NumStack_popItem(NumStack *self)
{
	float result = 0.0f;
	
	if (!NumStack_isEmpty(self))
	{
		result = self->data[self->top];
		self->top--;
	}

	return result;
}
