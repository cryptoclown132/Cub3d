NAME	= cub3d
LIBFT	= libft

CFLAGS	= -Wall -Wextra -Werror -g
MLX		= -Lmlx -lmlx -framework OpenGL -framework AppKit
# DEBUG	= -fsanitize=address

LIB_F = libft
LIB = libft/libft.a

SRC = ${shell echo src/*.c}

SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

OBJ = $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	cd libft && $(MAKE)
	$(CC) $(OBJ) $(MLX) $(DEBUG) $(LIB) -o $(NAME)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIB_F)

clean:
	$(RM) $(OBJ_PATH)
	cd libft && $(MAKE) clean
	$(RM) src/*.o MLX/*.o
	@make clean -C $(LIB_F)

	
re: fclean all