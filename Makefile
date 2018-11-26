
NAME = ft_ls

SRCS = main.c \
		input.c \
		output.c \
		sort_list.c \

LIB = -L libft/ -lft
OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

libft: 
	@ make -C ./libft
	@ echo "Libft done."

$(NAME): libft $(OBJ)
	@ gcc $(CFLAGS) -g $(OBJ) -o $(NAME) $(LIB) -I ./
	@ echo "Ft_ls done."

clean:
	/bin/rm -f $(OBJ)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $< -I libft/

.PHONY: all clean fclean re libft

.NOTPARALLEL: all clean fclean re libft
