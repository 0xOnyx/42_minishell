/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:34:12 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:34:13 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*current;

	current = (unsigned char *)dst;
	while (n--)
		current[n] = c;
	return (0);
}

int	ft_memcpy(void *dst, void *src, size_t len)
{
	while (len--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (0);
}

int	ft_bzero(void *dst, size_t size)
{
	return (ft_memset(dst, 0, size));
}
