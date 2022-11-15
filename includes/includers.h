/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerdos-s <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 22:31:22 by jerdos-s          #+#    #+#             */
/*   Updated: 2022/11/15 22:31:24 by jerdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDERS_H
# define INCLUDERS_H
# define NAME "Minishell"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
# include "data.h"
# include "utils.h"
# include "garbage.h"
# include "parser.h"
# include "minishell.h"

#endif
