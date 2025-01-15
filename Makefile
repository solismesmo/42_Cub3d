NAME		:= cub3D
NAME_BONUS		:= cub3D_bonus

CFLAGS	:= -g3 -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	:= ./includes/lib/MLX42
HEADERS	:= -I $(LIBMLX)/include -I
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
MK = mkdir -p

SOURCE_PATH = src/
SOURCE_BONUS_PATH = src_bonus/

SRCS	:= main.c

SRCS_BONUS	:= 

OBJECTS_PATH = objects
OBJS	:= $(addprefix $(OBJECTS_PATH)/, $(SRCS:%.c=%.o))

OBJECTS_BONUS_PATH = objects_bonus
OBJS_BONUS	:= $(addprefix $(OBJECTS_BONUS_PATH)/, $(SRCS_BONUS:%.c=%.o))

all:  libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJECTS_PATH)/%.o: $(SOURCE_PATH)%.c
	@$(MK) $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<) "

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

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

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS) 

re: fclean all

bre: fclean bonus

.PHONY: all clean fclean re libmlx