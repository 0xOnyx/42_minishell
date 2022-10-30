NAME = minishell

PATH_HEADER			= includes/
PATH_ROUTINE		= src_routine/
PATH_OBJ			= objs/

HEADER				= minishell.h
SRC_ROUTINE			= routine.c

SRC_ROUTINES		= $(addprefix $(PATH_ROUTINE),$(SRC_ROUTINE))

SRCS 				= $(SRC_ROUTINES)

OBJ					= $(SRCS:.c=.o)
OBJS				= $(addprefix $(PATH_OBJ),$(OBJ))
HEADERS				= $(addprefix $(PATH_HEADER),$(HEADER))

DEBUG				= -fsanitize=address -g3
CFLAGS				= -Wall -Werror -Wextra $(DEBUG)
LIBS				= -lreadline
CC					= gcc
RM					= rm -rf


$(PATH_OBJ)$(PATH_ROUTINE)%.o		: $(PATH_ROUTINE)%.c $(HEADERS)
	mkdir -p $(PATH_OBJ)$(PATH_ROUTINE)
	$(CC) $(CFLAGS) -o $(@) -c $(<) $(OPTIONS) -I./includes

all			: $(NAME)

$(NAME)		: $(OBJS)
	$(CC) $(CFLAGS) -I./includes $(LIB) -o $(@) $(^)

clean		:
	$(RM) $(OBJS)
	$(RM) $(PATH_OBJ)

fclean		: clean
	$(RM) $(NAME)

re			: fclean all

.PHONY: all fclean clean re


