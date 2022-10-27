NAME = minishell

PATH_HEADER = includes/
PATH_PARSER = src_parser/
PATH_ROUTINE = src_routine/

HEADER = minishell.h
SRC_PARSER = parser.c
SRC_ROUTINE = routine.c

CFLAGS = -Wall -Werror -Wextra
OPTIONS = -I$(PATH_HEADER)
LIBS  = -lreadline