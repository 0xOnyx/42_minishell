/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:33:37 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:33:38 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_close_in(int tube[2])
{
	close(tube[0]);
}

static void	dup_close_out(int tube[2], t_command *command)
{
	close(command->tmp_fd);
	dup2(tube[0], command->tmp_fd);
	close(tube[1]);
	close(tube[0]);
}

static void	heredoc_fork(char *end, int tube[2])
{
	char	*current;
	char	*tmp;
	char	*res;
	size_t	len;

	current = NULL;
	res = NULL;
	len = ft_strlen(end);
	printf("len for end -> %zu\n", len);
	dup_close_in(tube);
	printf("close is set current => %d\n", 1);
	while (1)
	{
		current = readline("heredoc>");
		if (ft_strncmp(current, end, len + 1) == 0)
			break ;
		if (ft_strjoin(&tmp, res, current))
			exit(1);
		del_malloc(res);
		free(current);
		res = tmp;
		if (ft_strjoin(&tmp, res, "\n"))
			exit(1);
		del_malloc(res);
		res = tmp;
	}
	res[ft_strlen(res)] = 0;
	free(current);
	ft_putstr_fd(res, tube[1]);
	del_malloc(res);
	exit(0);
}

int	heredoc(char *end, t_command *command)
{
	int		id;
	int		tube[2];

	printf("is inside heredoc \n");
	pipe(tube);
	id = fork();
	if (!id)
		heredoc_fork(end, tube);
	dup_close_out(tube, command);
	waitpid(id, NULL, 0);
	return (0);
}
