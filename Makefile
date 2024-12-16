NAME = pipex

CC	= gcc

CFLAGS	=	-Wall -Wextra -Werror

SRC_DIR	=	./srcs/

OBJ_DIR	=	./obj/

SRCS =	pipex.c \
		utils_pipex.c \

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: lib obj $(NAME) 

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I ./includes/ -I ./libft/ -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L ./libft -l ft -o $(NAME)

lib:
	make -C	./libft

clean:
	make clean -C ./libft
	rm -rf obj $(OBJS) 

fclean: clean
	make fclean -C ./libft
	rm -rf obj $(NAME) 

re: fclean all

.PHONY:     all clean fclean re
