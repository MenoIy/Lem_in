NAME = lem-in

FLAG = -Wall -Wextra -Werror

SRCS =	Sources/create_edges.c Sources/create_groups.c Sources/edmond_karp.c Sources/free_data.c Sources/ft_bfs.c Sources/ft_delete_double.c Sources/get_paths.c Sources/main.c \
				Sources/print_results.c Sources/store_data.c Sources/store_data2.c Sources/insert_ants.c

LIBFT = Libft/libft.a


OBJ_LEM = $(SRCS:.c=.o)

INC = -I includes/
INC_SRCS = includes/libft.h  includes/lem_in.h includes/get_next_line.h 

all: _libft $(NAME)

_libft:
		@make -C Libft

$(NAME): $(LIBFT) $(OBJ_LEM)
		@gcc -g $(OBJ_LEM) $(LIBFT) -o $(NAME)


$(OBJ_LEM): %.o : %.c $(INC_SRCS)
		@gcc -o $@ -c $< $(FLAG) $(INC)

clean:
		@make -C Libft/ clean
		@rm -f $(OBJ_LEM)

fclean: clean
		@make -C Libft/ fclean
		@rm -f $(NAME)
re: fclean all
