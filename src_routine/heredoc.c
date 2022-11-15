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

static void	dup_close_in(int tube[2], int fd)
{
	close(tube[1]);
	dup2(tube[1], fd);
	close(tube[0]);
}

static void	dup_close_out(int tube[2], int fd)
{
	dup2(tube[0], fd);
	close(tube[1]);
	close(tube[0]);
}

static void	heredoc_fork(int fd, char *end, int tube[2])
{
	char	*current;
	char	*tmp;
	char	*res;
	size_t	len;

	current = NULL;
	res = NULL;
	len = ft_strlen(end);
	dup_close_in(tube, fd);
	while (1)
	{
		current = readline("heredoc>");
		if (ft_strncmp(current, end, len + 1) == 0)
			break ;
		if (ft_strjoin(&tmp, current, res))
			exit(1);
		del_malloc(res);
		free(current);
		res = tmp;
	}
	free(current);
	ft_putstr_fd(res, fd);
	del_malloc(res);
	exit(0);
}

int	heredoc(int fd, char *end)
{
	int		id;
	int		tube[2];

	pipe(tube);
	id = fork();
	if (!id)
		heredoc_fork(fd, end, tube);
	waitpid(id, NULL, 0);
	dup_close_out(tube, fd);
	return (0);
}
