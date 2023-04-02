#include "monty.h"
/**
 * pall - prints all elements on the stack
 * @stack: The stack
 * @line_number: current line for bytecode
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void)line_number;
	temp = *stack;
	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * swap - The swap
 * @stack: stack to swap
 * @line_number: The line number
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp = (*stack)->n;

	if (!(*stack) || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		fclose(file);
		exit(EXIT_FAILURE);
	}

	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}

/**
 * add - Adds the first two elements
 * @stack: The stack
 * @line_number: number of bytecode
 */
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (!temp || !temp->next)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		free_stack(stack);
		err();
	}

	temp->next->n += temp->n;
	*stack = temp->next;
	(*stack)->prev = NULL;
	free(temp);
}

/**
 * nop - The nop
 * @stack: the stack
 * @line_number: line number
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
