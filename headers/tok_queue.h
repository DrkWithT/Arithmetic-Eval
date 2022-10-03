#ifndef TOK_QUEUE_H
#define TOK_QUEUE_H

#include "token.h"

/*
	Contains a data structure storing a "waiting line" of Tokens to process with
	Dijkstra's Shunt. Yard Algorithm. Single use per run: push everything before popping.
*/

struct tok_queue_obj
{
	int size;
	int front;
	int back;
	Token **data;
};

typedef struct tok_queue_obj Queue;

Queue *Create_Queue(int slots);

int Destroy_Queue(Queue *self);

int Queue_getSize(const Queue *self);

Token *Queue_popFront(Queue *self);

int Queue_pushBack(Queue *self, Token *tok);

#endif