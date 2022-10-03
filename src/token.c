#include "token.h"

Token *Create_Token(const char *raw_txt, TokenTypes type_code)
{
	Token *new_token = malloc(sizeof(Token));

	if (new_token != NULL) 
	{
		new_token->type = type_code;
		new_token->str = raw_txt;
	}
	
	return new_token;
}

int Destroy_Token(Token *self)
{
	int success = 0;

	if (self != NULL)
	{
		self->type = NIL;
		self->str = NULL; // str must have been set as static memory for argv[<some index>]... DO NOT FREE!
	}
	
	return success;
}

TokenTypes Token_getType(const Token *self) { return self->type; }

char *Token_toStr(Token *self) { return self->str; }
