#include "tok_queue.h"

Queue *Create_Queue(int slots)
{
	Queue *new_queue = malloc(sizeof(Queue));

	if (new_queue != NULL)
	{
		// validate slots parameter to avoid underflow-sizes
		if (slots > 0)
			new_queue->size = slots;
		else
			new_queue->size = 10;

		new_queue->front = 0;
		new_queue->back = -1;
		new_queue->data = calloc(new_queue->size, sizeof(Token *));

		// destroy / free this queue object if it's data is not allocated well
		if (!new_queue->data)
		{
			new_queue->size = 0;
			new_queue->front = 0;
			new_queue->back = 0;

			free(new_queue);
			new_queue = NULL;
		}
		else
		{
			// otherwise, default all Token slots to NULL for safety!
			for (int i = 0; i < new_queue->size; i++)
				new_queue->data[i] = NULL; // empty slot to be filled later...
		}
	}

	return new_queue;
}

// returns 0 if deallocation of inner data failed
int Destroy_Queue(Queue *self)
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
				Destroy_Token(self->data[index]); // reset a token's data
				self->data[index] = NULL; // detatch "reference" ptr to an original token
			}
		}

		// free dynamic array within this fixed size Queue...
		free(self->data);
	}

	return not_null && has_data;
}

int Queue_getSize(const Queue *self)
{
	return self->size;
}

Token *Queue_popFront(Queue *self)
{
	Token *result = NULL;

	// lazy delete front by moving queue ptr
	if (self->front <= self->back)
	{
		result = self->data[self->front];
		self->front++;
	}
	
	return result;
}

// returns 0 if pushing an item to the queue's back failed... The item must be pre-allocated by Create_Token()!
int Queue_pushBack(Queue *self, Token *tok)
{
	int can_push = self->back < self->size;
	
	if (can_push)
	{
		self->back++;
		self->data[self->back] = tok;
	}

	return can_push;
}