NAME= Cub3D

CC= cc
CFLAGS= -g -Wall -Werror -Wextra

SRC_MA= $(addprefix sources/main/, $(SOURCES_MAIN))
SOURCES_MAIN=	free_utils.c	\
				main.c			\
				initializer.c	\
				utils.c

SRC_PA= $(addprefix sources/parser/, $(SOURCES_PARSER))
SOURCES_PARSER=	parser.c

SRC_JU= $(addprefix sources/juggle/, $(SOURCES_JUGGLE))
SOURCES_JUGGLE=	hard_map.c		\
				mlx_window.c
		
OBJ_DIR= objects
OBJ=	$(addprefix $(OBJ_DIR)/, $(SRC_MA:sources/main/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_PA:sources/parser/%.c=%.o))\
		$(addprefix $(OBJ_DIR)/, $(SRC_JU:sources/juggle/%.c=%.o))

MLX_DIR= ./mlx
MLX= $(MLX_DIR)/libmlx_Linux.a -lXext -lX11 -lm -lz

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(MLX) $(LIBFT)

$(OBJ_DIR)/%.o: sources/main/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/parser/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/juggle/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run: re
	clear && ./Cub3D

.PHONY: all fclean clean re run