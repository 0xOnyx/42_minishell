#ifndef INCLUDERS_H
# define INCLUDERS_H

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
# include "utils.h"
# include "garbage.h"
# include "minishell.h"

typedef struct s_type		t_type;
typedef struct s_command	t_command;
typedef struct s_lexical	t_lexical;
typedef struct s_data		t_data;

t_data	*get_data(t_data *new_ptr);

#endif