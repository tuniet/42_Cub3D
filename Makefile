NAME		=		cub3D

INC_DIR		=		./include
HEADER_FILE	=		$(INC_DIR)/cub3D.h
LIBFT		=		libft
SRC_DIR		=		./src
SRCS		=		$(addprefix $(SRC_DIR)/, \
					main.c \
					parsing.c file_check.c)

OBJ_DIR		=		./obj
OBJS		=		$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#CFLAGS		=		-Wall -Wextra -Werror
CFLAGS		=		-g -fsanitize=address -Wall -Wextra -Werror
CC			=		cc

all:	${NAME}

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME) $(LDFLAGS) && \
	(printf "cub3D compiled successfully.\n")

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER_FILE)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@printf "cub3D object files cleaned.\n"

fclean: clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@make -s -C $(LIBFT) fclean
	@printf "cub3D cleaned successfully.\n"

re:	fclean all

.PHONY:	all clean fclean re
