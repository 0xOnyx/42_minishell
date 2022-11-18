/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:33:01 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:33:02 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_dquote(int *i, char c)
{
	if (c == '"' && *i == 0)
		*i += 1;
	else if (c == '"' && *i == 1)
		*i -= 1;
}

void	in_squote(int *i, char c)
{
	if (c == '\'' && *i == 0)
		*i += 1;
	if (c == '\'' && *i == 1)
		*i -= 1;
}

void	is_in_dquote(int *i, char c, int quotes)
{
	if (c == '"' && !quotes)
		*i += 1;
}

void	is_in_squote(int *i, char c, int quotes)
{
	if (c == '\'' && !quotes)
		*i += 1;
}
