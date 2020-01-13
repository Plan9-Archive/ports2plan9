/*
 * This file is part of LibParserUtils.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2008 John-Mark Bell <jmb@netsurf-browser.org>
 */

#if defined PLAN9
#include <limits.h>
#define INT32_MAX INT_MAX
#endif

#include <inttypes.h>
#include <string.h>

#include <parserutils/utils/stack.h>

/**
 * Stack object
 */
struct parserutils_stack
{
	size_t item_size;		/**< Size of an item in the stack */
	size_t chunk_size;		/**< Size of a stack chunk */
	size_t items_allocated;		/**< Number of slots allocated */
	int32_t current_item;		/**< Index of current item */
	void *items;			/**< Items in stack */

	parserutils_alloc alloc;	/**< Memory (de)allocation function */
	void *pw;			/**< Client-specific data */
};

/**
 * Create a stack
 *
 * \param item_size   Length, in bytes, of an item in the stack
 * \param chunk_size  Number of stack slots in a chunk
 * \param alloc       Memory (de)allocation function
 * \param pw          Pointer to client-specific private data
 * \param stack       Pointer to location to receive stack instance
 * \return PARSERUTILS_OK on success,
 *         PARSERUTILS_BADPARM on bad parameters
 *         PARSERUTILS_NOMEM on memory exhaustion
 */
parserutils_error parserutils_stack_create(size_t item_size, size_t chunk_size,
		parserutils_alloc alloc, void *pw, parserutils_stack **stack)
{
	parserutils_stack *s;

	if (item_size == 0 || chunk_size == 0 || alloc == NULL || stack == NULL)
		return PARSERUTILS_BADPARM;

	s = alloc(NULL, sizeof(parserutils_stack), pw);
	if (s == NULL)
		return PARSERUTILS_NOMEM;

	s->items = alloc(NULL, item_size * chunk_size, pw);
	if (s->items == NULL) {
		alloc(s, 0, pw);
		return PARSERUTILS_NOMEM;
	}

	s->item_size = item_size;
	s->chunk_size = chunk_size;
	s->items_allocated = chunk_size;
	s->current_item = -1;

	s->alloc = alloc;
	s->pw = pw;

	*stack = s;

	return PARSERUTILS_OK;
}

/**
 * Destroy a stack instance
 *
 * \param stack  The stack to destroy
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_stack_destroy(parserutils_stack *stack)
{
	if (stack == NULL)
		return PARSERUTILS_BADPARM;

	stack->alloc(stack->items, 0, stack->pw);
	stack->alloc(stack, 0, stack->pw);

	return PARSERUTILS_OK;
}

/**
 * Push an item onto the stack
 *
 * \param stack  The stack to push onto
 * \param item   The item to push
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_stack_push(parserutils_stack *stack, 
		const void *item)
{
	int32_t slot;

	if (stack == NULL || item == NULL)
		return PARSERUTILS_BADPARM;

	/* Ensure we'll get a valid slot */
	if (stack->current_item < -1 || stack->current_item == INT32_MAX)
		return PARSERUTILS_INVALID;

	slot = stack->current_item + 1;

	if ((size_t) slot >= stack->items_allocated) {
		void *temp = stack->alloc(stack->items,
				(stack->items_allocated + stack->chunk_size) *
				stack->item_size, stack->pw);
		if (temp == NULL)
			return PARSERUTILS_NOMEM;

		stack->items = temp;
		stack->items_allocated += stack->chunk_size;
	}

	memcpy((uint8_t *) stack->items + (slot * stack->item_size), 
			item, stack->item_size);
	stack->current_item = slot;

	return PARSERUTILS_OK;
}

/**
 * Pop an item off a stack
 *
 * \param stack  The stack to pop from
 * \param item   Pointer to location to receive popped item, or NULL
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_stack_pop(parserutils_stack *stack, void *item)
{
	if (stack == NULL)
		return PARSERUTILS_BADPARM;

	if (stack->current_item < 0)
		return PARSERUTILS_INVALID;

	if (item != NULL) {
		memcpy(item, (uint8_t *) stack->items + 
				(stack->current_item * stack->item_size), 
				stack->item_size);
	}

	stack->current_item -= 1;

	return PARSERUTILS_OK;
}

/**
 * Retrieve a pointer to the current item on the stack
 *
 * \param stack  The stack to inspect
 * \return Pointer to item on stack, or NULL if none
 */
void *parserutils_stack_get_current(parserutils_stack *stack)
{
	if (stack == NULL || stack->current_item < 0)
		return NULL;

	return (uint8_t *) stack->items + 
			(stack->current_item * stack->item_size);
}

#ifndef NDEBUG
#include <stdio.h>

extern void parserutils_stack_dump(parserutils_stack *stack, const char *prefix,
		void (*printer)(void *item));

void parserutils_stack_dump(parserutils_stack *stack, const char *prefix,
		void (*printer)(void *item))
{
	int32_t i;

	if (stack == NULL || printer == NULL)
		return;

	for (i = 0; i <= stack->current_item; i++) {
		printf("%s %d: ", prefix != NULL ? prefix : "", i);
		printer((uint8_t *) stack->items + (i * stack->item_size));
		printf("\n");
	}
}

#endif

