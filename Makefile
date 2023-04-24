NAME	= cub3d
LIBFT	= libft

CFLAGS	= -Wall -Wextra -Werror -g
MLX		= -Lmlx -lmlx -framework OpenGL -framework AppKit
# DEBUG	= -fsanitize=address

LIB_F = libft
LIB = libft/libft.a

# SRC		=	sauce/main.c \
# 			sauce/delete_later.c \
# 			sauce/error.c \
# 			sauce/cub_utils.c \
# 			sauce/00_check_map.c \
# 			sauce/01_check_map.c \
# 			sauce/00_parse.c \
# 			sauce/01_parse.c \
# 			sauce/get_next_line.c \
# 			sauce/raycast.c \
# 			sauce/keyevents.c
SRC = ${shell echo sauce/*.c}

SRC_PATH = sauce/
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
	$(RM) sauce/*.o MLX/*.o
	@make clean -C $(LIB_F)

	
re: fclean all