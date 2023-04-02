#include "monty.h"

FILE *file = NULL;

/**
 * main - runs monty bytecode
 * @argc: argument count
 * @argv: argument vector
 * Return: depends on success
 */
int main(int argc, char **argv)
{
	void (*f)(stack_t **, unsigned int) = NULL;
	char *buffer = NULL, op[50] = {'\0'}, pushNum[50] = {'\0'}, *token = NULL;
	size_t bufsize = 0;
	stack_t *stack = NULL;
	unsigned int line_number = 1;

	if (argc != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);
	file = fopen(argv[1], "r");
	if (!file)
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);
	for (; getline(&buffer, &bufsize, file) != EOF; line_number++)
	{
		token = strtok((buffer), " \t\n");
		if (!token)
		{
			free(buffer), buffer = NULL;
			continue;
		}
		strcpy(op, token);
		f = get_func(&stack, line_number, op);
		if (!f)
			fprintf(stderr, "Error: malloc failed\n"), err();
		if (strcmp(op, "push") == 0)
		{
			token = strtok(NULL, " \t\n");
			if (!token)
			{
				free(buffer), buffer = NULL, free_stack(&stack);
				fprintf(stderr, "L%d: usage: push integer\n", line_number), err();
			}
			strcpy(pushNum, token);
		}
		free(buffer), buffer = NULL;
		f(&stack, line_number);
		if (strcmp(op, "push") == 0)
			pushOp(&stack, line_number, pushNum);
	}
	free(buffer), fclose(file), free_stack(&stack);
	return (EXIT_SUCCESS);
}

/**
 * get_func - Finds function
 * @stack: The stack
 * @code: The code
 * @l: The line number
 * Return: depends
 */
void (*get_func(stack_t **stack, int l, char *code))(stack_t **, unsigned int)
{
	instruction_t instruction[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop}
	};

	int i = 0;

	while (strcmp(code, instruction[i].opcode) != 0)
	{
		i++;
		if (i > 7)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", l, code);
			free_stack(stack);
			err();
		}
	}
	return (instruction[i].f);
}
/**
 * err - error handling
 */
void err(void)
{
	fclose(file);
	exit(EXIT_FAILURE);
}

/**
 * pushOp - Helps the push argument
 * @stack: The stack
 * @line_number: The line number
 * @pushNum: new node
 */
void pushOp(stack_t **stack, unsigned int line_number, char *pushNum)
{
	if (strcmp(pushNum, "0") == 0)
		(*stack)->n = 0;
	if (strcmp(pushNum, "0") != 0)
	{
		(*stack)->n = atoi(pushNum);
		if ((*stack)->n == 0 || (pushNum[0] != '-' && (*stack)->n == -1))
		{
			fprintf(stderr, "Error: L%d: usage: push integer\n", line_number);
			free_stack(stack);
			err();
		}
	}
}

/**
 * free_stack: frees the stack
 * @stack: the stack
 */
void free_stack(stack_t **stack)
{
	if (!(stack) || !(*stack))
	{
		return;
	}
	free_stack(&((*stack)->next));
	free(*stack);
	*stack = NULL;
}
