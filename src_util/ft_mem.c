#include "utils.h"

int ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*current;

	current = (unsigned char *)dst;
	while (n--)
		current[n] = c;
	return (0);
}

int ft_memcpy(void *src, void *dst, size_t len)
{
	while (len--)
		*((unsigned char *)dst++) = *((unsigned char *)src++);
	return (0);
}