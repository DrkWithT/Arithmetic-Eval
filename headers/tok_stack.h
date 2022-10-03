#ifndef TOK_STACK_H
#define TOK_STACK_H

/*
	Array implementation of operator or operand stack. Tokens will be processed by other code, but this stack only contains raw tokens.
*/

#include "token.h"

struct tok_stk_obj
{
	int size;  // count of Tokens
	int top;   // index to access data for top element
	Token **data; // store ptrs to Tokens
};

typedef struct tok_stk_obj Stack;

Stack *Create_Stack(int slots);

int Destroy_Stack(Stack *self);

int Stack_getSize(const Stack *self);

int Stack_isFull(const Stack *self);

int Stack_isEmpty(const Stack *self);

int Stack_pushItem(Stack *self, Token *tok);

Token *Stack_peekItem(const Stack *self);

Token *Stack_popItem(Stack *self);

#endif