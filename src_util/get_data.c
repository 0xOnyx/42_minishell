/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:34:22 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:34:23 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(t_data *new_ptr)
{
	static t_data	*addr;

	if (new_ptr)
		addr = new_ptr;
	return (addr);
}
