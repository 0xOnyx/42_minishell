NAME = minishell

PATH_HEADER = includes/
PATH_PARSER = src_parser/
PATH_ROUTINE = src_routine/
PATH_OBJ = objs/

HEADER = minishell.h
SRC_PARSER = parser.c
SRC_ROUTINE = routine.c

SRC_PARSER = $(addprefix $(PATH_PARSER),$(SRC_PARSER))
SRC_ROUTINE = $(addprefix $(PATH_ROUTINE),$(SRC_ROUTINE))
OBJ = $(SRCS:.c=.o)

SRCS = SRC_PARSER + SRC_ROUTINE
OBJS = $(addprefix $(PATH_OBJ),$(SRCS))
HEADERS = $(addprefix $(PATH_HEADER),$(HEADER))

CFLAGS = -Wall -Werror -Wextra
OPTIONS = -I$(PATH_HEADER)
LIBS  = -lreadline
CC = gcc
RM = rm -rf

$(PATH_OBJ)%.o: $(PATH_ROUTINE)%.c $(HEADERS)
	mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $(@) $(<)

$(PATH_OBJ)%.o: $(PATH_PARSER)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(OPTIONS) -o $(@) $(<)


all: $(NAME)
	mkdir -p $(PATH_OBJS)
	$(CC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTIONS) $(LIB) -o $(@) -$(^)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re


