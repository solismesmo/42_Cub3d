# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: livieira < livieira@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 13:30:54 by bgomes-l          #+#    #+#              #
#    Updated: 2025/04/02 22:23:43 by livieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

M_SRC = ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcpy.c \
	ft_strrchr.c ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c \
	ft_strlen.c ft_tolower.c ft_calloc.c ft_isdigit.c ft_memcpy.c \
	ft_strdup.c ft_strncmp.c ft_toupper.c ft_isalnum.c ft_isprint.c \
	ft_memmove.c ft_strlcat.c ft_strnstr.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_printf_bonus.c ft_printf_utils_bonus.c ft_printf_utils2_bonus.c \
	get_next_line_utils.c get_next_line.c
	


B_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

M_OBJ = $(M_SRC:%.c=%.o)

B_OBJ = $(B_SRC:%.c=%.o)

HEADER = libft.h

FLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(M_OBJ)

bonus: $(B_OBJ)

%.o: %.c $(HEADER)
	@cc $(FLAGS) -c $< -o $@
	@ar -rcs $(NAME) $@

clean:
	@rm -f $(M_OBJ) $(B_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

rebonus: fclean all bonus

.PHONY:		all clean fclean re bonus rebonus
