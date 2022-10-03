#include "num_stack.h"
#include "tok_queue.h"
#include "tok_stack.h"
#include <stdio.h>
#include <string.h>

int isNumber(const char *str) {
  // handle valid [0-9] float literals and the special "0" case!
  return atof(str) != 0 || (strlen(str) == 1 && str[0] == '0');
}

int getOpPrecedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1; // add, sub are lowest precedence
  case 'x':
  case '/':
    return 2; // mul, div are higher precedence than add, sub
  default:
    return -1; // unsupported operator
  }
}

int isOperator(const char *str) { return getOpPrecedence(str[0]) != -1; }

Token **makeTokens(int raw_args_len, char *raw_args[]) {
  Token **tokens = malloc(raw_args_len * sizeof(Token));

  if (tokens != NULL) {
		// read args after program name!
    for (size_t i = 1; i < raw_args_len; i++) {
      TokenTypes temp_type;

      if (isNumber(raw_args[i]))
        temp_type = NUM;
      else if (isOperator(raw_args[i]))
        temp_type = OPR;
      else
        temp_type = NIL;
			
      tokens[i - 1] = Create_Token(raw_args[i], temp_type);
    }
  }

  return tokens;
}

// NOTE: tokc must not include program name from argv, so it is `argc - 1`.
int doShuntingYard(int tokc, Token **input, Stack *operators, Queue *output) {
	int has_invalid_tok = 0; // if error like a NIL type token is found
  int input_idx = 0; // reading index of token array

  while (input_idx < tokc) {
    Token *temp_input_tok = input[input_idx];

		// ignore null tokens
    if (!temp_input_tok)
		{
			input_idx++;
			continue;
		}
		
    // get token literal string for checking only!
    char *token_txt = Token_toStr(temp_input_tok);

    if (Token_getType(temp_input_tok) == NUM)
		{
      // if a number is found, push it to the output queue
      Queue_pushBack(output, temp_input_tok);
    }
		else if (Token_getType(temp_input_tok) == OPR)
		{
      // while the operator stack has something...
      while (1)
			{
				if (Stack_isEmpty(operators))
					break;
				
				char *temp_op2 = Token_toStr(Stack_peekItem(operators));
				
        // when the 2nd operator has precedence >= to 1st (prev) operator, pop it to the output queue!
        if (getOpPrecedence(temp_op2[0]) < getOpPrecedence(token_txt[0]))
					break;
				
        Queue_pushBack(output, Stack_popItem(operators));
			}

      // push current operator to the operators' stack anyway
      Stack_pushItem(operators, temp_input_tok);
    }
		else
		{
			// handle invalid token error case
			puts("invalid token!");
			has_invalid_tok = 1;
			goto handleErr;
		}
		
    input_idx++;
  }

  // put in remaining operators to output queue...
  while (!Stack_isEmpty(operators))
    Queue_pushBack(output, Stack_popItem(operators));
	
	handleErr: // handling point for ANY error

  return !has_invalid_tok;
}

// Does a basic int arithmetic operation on 2 ints. Sets `*err_ptr` to 1 on error. 
float evalOp(float a, float b, int *err_ptr, char op)
{
	float result = 0;

	switch (op)
	{
		case '+':
			result = a + b;
			break;
		case '-':
			result = b - a;
			break;
		case 'x':
			result = a * b;
			break;
		case '/':
			if (a != 0.0)
				result = b / a;
			else
				*err_ptr = 1; // set error flag for div by 0
			break;
		default:
			*err_ptr = 1; // set error flag for invalid operator
			break;
	}

	return result;
}

// Uses another stack to evaluate RPN from the shunting yard algo. Sets `*err_ptr` to 1 on error.
float evalRPN(Queue *rpn, NumStack *eval_stk, int *err_ptr)
{
	// temp ptrs to tokens
	Token *temp1 = NULL;
	char *temp_literal = NULL;

	// operands
	float a = 0;
	float b = 0;
	float temp_result = 0;
	
	do
	{
		// put operands on eval_stk, and pop 2 operands when an op is found before an operation
		temp1 = Queue_popFront(rpn);

		// ignore null tokens
		if (!temp1)
			continue;

		temp_literal = Token_toStr(temp1);

		// process token for eval
		if (Token_getType(temp1) == NUM)
			NumStack_pushItem(eval_stk, atof(temp_literal));
		else if (Token_getType(temp1) == OPR)
		{
			a = NumStack_popItem(eval_stk);
			b = NumStack_popItem(eval_stk);

			temp_result = evalOp(a, b, err_ptr, temp_literal[0]);
			NumStack_pushItem(eval_stk, temp_result);
		}
		else
		{
			// check for any invalid token error
			*err_ptr = 1;
			return -1;
		}

		// check for any eval error
		if (*err_ptr == 1)
			return -1;
		
	} while (temp1 != NULL);

	return NumStack_peekTop(eval_stk);
}

int main(int argc, char *argv[])
{
  /// 0. validate count of args after program name
  if (argc <= 1)
	{
    printf("Usage: main <operand> <operator> ...\n");
    return 1;
  }

  /// 1. construct all objects...
  Token **input_toks = makeTokens(argc, argv); // list of input tokens
  Stack *ops = Create_Stack(argc); // operator stack for infix notation to RPN conversion
  Queue *output_toks = Create_Queue(argc); // ordered queue of output tokens in RPN
	NumStack *eval_stack = Create_NumStack(argc); // stack for holding operators during RPN eval
	
  /// 2a. do shunting yard algo on token stacks...
  int success = doShuntingYard(argc - 1, input_toks, ops, output_toks);

  if (!success)
	{
    perror("Error: RPN conversion failed.\n");
    goto handleFail;
  }

	/// 3. Eval the RPN within the output stack?
	int err_flag = 0;
	float answer = evalRPN(output_toks, eval_stack, &err_flag);

	if (err_flag)
	{
		perror("Found invalid operator.\n");
		goto handleFail;
	}
	else
		printf("\nAns: %g\n", answer);
	
/// 4. cleanup
handleFail: // error handling point in case a null token is found

	// Unbind token reference ptrs from within each stack and queue.
	Destroy_NumStack(eval_stack);
	free(eval_stack);
	eval_stack = NULL;

  Destroy_Queue(output_toks);
  free(output_toks);
  output_toks = NULL;

  Destroy_Stack(ops);
  free(ops);
  ops = NULL;

	// NOTE: Freeing just the originally allocated tokens still cleans all memory I think. This is because the stacks and queues only store reference ptrs to the original Tokens, not the real data.
  for (int free_idx = 0; free_idx < argc; free_idx++)
	{
    if (input_toks[free_idx] != NULL)
      free(input_toks[free_idx]);
  }

	// Deallocate "outer" memory storing pointer addresses to Tokens.
  free(input_toks);
  input_toks = NULL;

  return 0;
}