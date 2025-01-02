NAME        = cub3d
LIBFT       = ./Libft/libft/libft.a
LIBFT_DIR   = ./Libft/libft
MLX_DIR     = ./minilibx-linux

CC          = cc -Wextra -Werror -Wall
CFLAGS      = -Imlx -g

MLXFLAGS    = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC   		= main \
				init \
				exit \
				utils \
				rendering \
				vector_func \
				event \
				check_map_validity \
				check_map_validity_utils \
				graphical_info \
				graphical_info_utils \
				process_map \
				parse_input_file \
				draw \
				texture \
				raycasting 
 

SRCS	= $(addsuffix .c, $(SRC))

OBJS    = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@echo "Building $(NAME)..."

	@make -C $(LIBFT_DIR)

	@echo "Checking minilibx submodule..."
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Initializing minilibx submodule..."; \
		git submodule update --init --recursive minilibx-linux; \
	else \
		echo "Updating minilibx submodule..."; \
		git submodule update --recursive minilibx-linux; \
	fi
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $@

clean:
	@echo "Cleaning up..."
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS)
			
fclean: clean
	@rm -rf $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re