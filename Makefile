NAME= minishell

CC= cc
CFLAGS= -g -Wall -Werror -Wextra

SRC_BI= $(addprefix sources/main/, $(SOURCES_MAIN))
SOURCES_MAIN=	main.c				

SRC_PA= $(addprefix sources/parser/, $(SOURCES_PARSER))
SOURCES_PARSER=		parcer.c
		
OBJ_DIR= objects
OBJ=	$(addprefix $(OBJ_DIR)/, $(SRC_EX:sources/main/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_PA:sources/parser/%.c=%.o))

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: sources/main/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/parser/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run: re
	clear && ./minishell

.PHONY: all fclean clean re run