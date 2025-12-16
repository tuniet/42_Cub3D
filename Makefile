NAME		=		cub3D

INC_DIR		=		./include
HEADER_FILE	=		$(INC_DIR)/cub3D.h
DEPS_DIR	=		./dependencies
LIBFT		=		$(DEPS_DIR)/libft
MLX			=		$(DEPS_DIR)/mlx
SRC_DIR		=		./src
SRCS		=		$(addprefix $(SRC_DIR)/, \
					main.c \
					file_check.c \
					draw.c \
					raycasting.c \
					load_text.c \
					parser.c \
					keys.c move.c play.c)

OBJ_DIR		=		./obj
OBJS		=		$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#CFLAGS		=		-Wall -Wextra -Werror
CFLAGS		=		-g -fsanitize=address -Wall -Wextra
MLXFLAGS	=		-L$(MLX) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_FLAGS	=		-L$(LIBFT) -lft
CC			=		cc

all:	${NAME}

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLXFLAGS) -o $(NAME) && \
	(printf "cub3D compiled successfully.\n")

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER_FILE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -s -C $(MLX) clean
	@printf "cub3D object files cleaned.\n"

fclean: clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@make -s -C $(LIBFT) fclean
	@printf "cub3D cleaned successfully.\n"

re:	fclean all

.PHONY:	all clean fclean re
