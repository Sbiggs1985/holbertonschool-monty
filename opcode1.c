#include "monty.h"

/**
 * push - Adds an element to a stack
 * @stack: stack to push
 * @line_number: Line number of bytecode
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newNode;

	newNode = malloc(sizeof(stack_t));

	if (!newNode)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(stack);
		err();
	}

	(void)line_number;

	if (*stack)
		(*stack)->prev = newNode;

	newNode->prev = NULL;
	newNode->next = *stack;
	newNode->n = 0;
	*stack = newNode;
}

/**
 * pop - Removes the first element
 * @stack: stack to pop
 * @line_number: number of bytecode file
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	temp = *stack;

	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		fclose(file);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}

	*stack = temp->next;

	if (*stack)
		(*stack)->prev = NULL;
	free(temp);
}

/**
 * pint - prints the value
 * @stack: Stack to pint
 * @line_number: number of bytecode file
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		fclose(file);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}
