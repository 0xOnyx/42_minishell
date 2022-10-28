NAME = minishell

PATH_HEADER = includes/
PATH_PARSER = src_parser/
PATH_ROUTINE = src_routine/
PATH_OBJ = objs/

HEADER = minishell.h
SRC_PARSER = parser.c
SRC_ROUTINE = routine.c

SRC_PARSERS = $(addprefix $(PATH_PARSER),$(SRC_PARSER))
SRC_ROUTINES = $(addprefix $(PATH_ROUTINE),$(SRC_ROUTINE))

SRCS = $(SRC_PARSERS) $(SRC_ROUTINES)

OBJ = $(SRCS:.c=.o)
OBJS = $(addprefix $(PATH_OBJ),$(OBJ))
HEADERS = $(addprefix $(PATH_HEADER),$(HEADER))

CFLAGS = -Wall -Werror -Wextra
OPTIONS = -I$(PATH_HEADER)
LIBS  = -lreadline
CC = gcc
RM = rm -rf

$(PATH_OBJ)$(PATH_ROUTINE)%.o: $(PATH_ROUTINE)%.c $(HEADERS)
	mkdir -p $(PATH_OBJS)$(PATH_ROUTINE)
	$(CC) $(CFLAGS) $(OPTIONS) -o $(@) $(<)

$(PATH_OBJ)$(PATH_PARSER)%.o: $(PATH_PARSER)%.c $(HEADERS)
	mkdir -p $(PATH_OBJS)$(PATH_PARSER)
	$(CC) $(CFLAGS) $(OPTIONS) -o $(@) $(<)

test:
	@echo $(OBJS)

all: $(NAME)
	$(CC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTIONS) $(LIB) -o $(@) -$(^)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re


