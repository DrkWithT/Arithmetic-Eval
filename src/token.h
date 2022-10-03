#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

/*
	Stores data of a single operator or operand literal: type and text.
*/

enum tok_types
{
	NIL,
	NUM, // number
	OPR  // operator
};

typedef enum tok_types TokenTypes;

struct tok_obj
{
	TokenTypes type; // enumerated type indicating what kind of token is this
	char *str; // points to a const char *s like argv[n]
};

typedef struct tok_obj Token;

Token *Create_Token(const char *raw_txt, TokenTypes type_code);

int Destroy_Token(Token *self);

TokenTypes Token_getType(const Token *self);

char *Token_toStr(Token *self);

#endif