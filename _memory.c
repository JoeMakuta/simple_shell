#include "entry.h"

/**
 * _mcpy - Copies information between void pointers.
 * @nptr: destination pointer.
 * @ptr: source pointer.
 * @s: size of the new pointer.
 *
 * Return: no return.
 */
void _mcpy(void *nptr, const void *ptr, unsigned int s)
{
	char *c_ptr = (char *)ptr;
	char *c_nptr = (char *)nptr;
	unsigned int i;

	for (i = 0; i < s; i++)
		c_nptr[i] = c_ptr[i];
}

/**
 * _ralloc - Reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @o_size: size, in bytes, of the allocated space of ptr.
 * @n_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 */
void *_ralloc(void *ptr, unsigned int o_size, unsigned int n_size)
{
	void *n_ptr;

	if (ptr == NULL)
		return (malloc(n_size));

	if (n_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (n_size == o_size)
		return (ptr);

	n_ptr = malloc(n_size);
	if (n_ptr == NULL)
		return (NULL);

	if (n_size < o_size)
		_mcpy(n_ptr, ptr, n_size);
	else
		_mcpy(n_ptr, ptr, o_size);

	free(ptr);
	return (n_ptr);
}

/**
 * _rallocdp - Reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @o_size: size, in bytes, of the allocated space of ptr.
 * @n_size: new size, in bytes, of the new memory block.
 *
 * Return: A new ptr.
 */
char **_rallocdp(char **ptr, unsigned int o_size, unsigned int n_size)
{
	char **n_ptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * n_size));

	if (n_size == o_size)
		return (ptr);

	n_ptr = malloc(sizeof(char *) * n_size);
	if (n_ptr == NULL)
		return (NULL);

	for (i = 0; i < o_size; i++)
		n_ptr[i] = ptr[i];

	free(ptr);

	return (n_ptr);
}
