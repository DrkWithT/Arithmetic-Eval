#include "tok_stack.h"

// returns 0 if allocation of the stack or its data failed
Stack *Create_Stack(int slots)
{
	Stack *new_stack = malloc(sizeof(Stack));

	if (new_stack != NULL)
	{
		// validate slots parameter to avoid underflow-sizes
		if (slots > 0)
			new_stack->size = slots;
		else
			new_stack->size = 10;
		
		new_stack->top = -1;
		new_stack->data = calloc(new_stack->size, sizeof(Token *));

		// check if data array allocated ok... if not, the stack is unusable!
		if (!new_stack->data)
		{
			new_stack->size = 0;
			new_stack->top = -1;
			
			free(new_stack);
			new_stack = NULL;
		}
		else
		{
			// default Token ptrs to NULL for safety
			for(int i = 0; i < new_stack->size; i++)
				new_stack->data[i] = NULL;
		}
	}

	return new_stack;
}

// Returns 0 (false) if deallocation of data failed. BUT: original token ptrs are freed in `./main.c`!
int Destroy_Stack(Stack *self)
{
	int not_null = self != NULL;
	int has_data = 0;
		
	if (not_null)
		has_data = self->data != NULL;

	if (has_data)
	{
		// free all dynamic memory for Tokens within data...
		for (int index = 0; index < self->size; index++)
		{
			if (self->data[index] != NULL)
			{
				Destroy_Token(self->data[index]); // actually resets token data instead of freeing it
				self->data[index] = NULL; // detatch "reference" ptr to token
			}
		}

		// free dynamic array within Stack...
		free(self->data);
	}

	return not_null && has_data;
}

int Stack_getSize(const Stack *self)
{
	return self->size;
}

int Stack_isFull(const Stack *self)
{
	return self->top >= self->size - 1;
}

int Stack_isEmpty(const Stack *self)
{
	return self->top <= -1 || self->size == 0;
}

// returns 0 if pushing the item failed... The item must be pre-allocated before pushing it.
int Stack_pushItem(Stack *self, Token *tok)
{
	int can_push = !Stack_isFull(self);

	if (can_push)
	{
		self->top++;
		self->data[self->top] = tok;
	}

	return can_push;
}

Token *Stack_peekItem(const Stack *self)
{
	Token *result = NULL;
	int has_anything = !Stack_isEmpty(self);

	if (has_anything)
		result = self->data[self->top];

	return result;
}

// returns NULL on pop failure only when the stack is empty
Token *Stack_popItem(Stack *self)
{
	int can_pop = !Stack_isEmpty(self);
	Token *item = NULL;
	
	if (can_pop)
	{
		item = self->data[self->top];
		self->top--; // lazily delete top before the pop
	}

	return item;
}