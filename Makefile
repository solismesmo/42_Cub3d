NAME		:= cub3D
NAME_BONUS		:= cub3D_bonus

CFLAGS	:= -g3 -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	:= ./includes/lib/MLX42
LIBFT	:= ./includes/libft
HEADERS	:= -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
MK = mkdir -p

SOURCE_PATH = src/
SOURCE_BONUS_PATH = src_bonus/

LIBFT_PATH = ./includes/libft/
LIBFT = ./includes/libft/libft.a

SRCS	:= main.c map_check_utils.c map_check_utils_II.c map_check_utils_III.c \
			open_close_args.c free_error.c raycasting.c moviment.c


OBJECTS_PATH = objects
OBJS	:= $(addprefix $(OBJECTS_PATH)/, $(SRCS:%.c=%.o))


all: $(LIBFT) libmlx $(NAME)

$(LIBFT): 
	make -C $(LIBFT_PATH)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJECTS_PATH)/%.o: $(SOURCE_PATH)%.c
	@$(MK) $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<) "

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME)

bonus: libmlx $(NAME_BONUS)

$(OBJECTS_BONUS_PATH)/%.o: $(SOURCE_BONUS_PATH)%.c
	@$(MK) $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<) "

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBFT) $(LIBS) $(HEADERS) -o $(NAME_BONUS)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@rm -rf $(LIBMLX)/build 
	@rm -rf $(OBJECTS_PATH)
	@rm -rf $(OBJECTS_BONUS_PATH)
	@rm -rf $(LIBFT_PATH)/*.o


fclean: clean
	@rm -rf $(NAME) $(LIBFT) $(NAME_BONUS) 

re: fclean all

bre: fclean bonus

.PHONY: all clean fclean re libmlx