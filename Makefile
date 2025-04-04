NAME		:= cub3D
CFLAGS	:= -g3 -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	:= ./includes/lib/MLX42
LIBFT	:= ./includes/libft
HEADERS	:= -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
MK = mkdir -p
SOURCE_PATH = src/
LIBFT_PATH = ./includes/libft/
LIBFT = ./includes/libft/libft.a

SRCS	:= main.c map_check_utils.c map_check_utils_II.c \
			open_close_args.c free_error.c raycasting.c moviment.c \
			draw.c dda.c map_check.c init_values.c init_map.c \
			parsing.c color.c utils.c textures.c image.c \
			calculate.c calculate_II.c


OBJECTS_PATH = objects
OBJS	:= $(addprefix $(OBJECTS_PATH)/, $(SRCS:%.c=%.o))


all: $(LIBFT) libmlx $(NAME)

$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_PATH)
	@echo "Libft is ready!"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJECTS_PATH)/%.o: $(SOURCE_PATH)%.c
	@$(MK) $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "Compiling Cub3D..."
	@$(CC) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "Lets play!"

clean:
	@echo "Cleaning only the object files."
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@rm -rf $(LIBMLX)/build 
	@rm -rf $(OBJECTS_PATH)
	@rm -rf $(OBJECTS_BONUS_PATH)
	@rm -rf $(LIBFT_PATH)/*.o
	@echo "Without object files."

fclean: clean
	@echo "Now it's a full cleanup"
	@rm -rf $(NAME) $(LIBFT)
	@echo "All clean"

re: fclean all

bre: fclean bonus

.PHONY: all clean fclean re libmlx
