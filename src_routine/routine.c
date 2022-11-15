/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:35:27 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:35:31 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	data = (t_data){};
	get_data(&data);
	if (init_env(env))
	{
		free_all();
		return (1);
	}
	minishell();
	free_all();
	return (0);
}
