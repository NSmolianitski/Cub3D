
NAME	=	libftprintf.a

SRCS	=	cub3d.c libft/ft_atoi.c libft/libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_lstnew.c libft/ft_lstadd_front.c libft/ft_lstsize.c libft/ft_lstlast.c libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c libft/ft_lstiter.c libft/ft_lstmap.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parser/cub_parser.c parser/map_parser.c parser/resolution_parser.c parser/settings_parser.c parser/texture_and_color_parser.c utils/cub_errors.c utils/cub_str_utils.c utils/cub_utils.c

HEADERS	=	includes/cub3d.h includes/cub_parser.h includes/cub_utils.h includes/get_next_line.h		\
			includes/mlx.h includes/libft.h

CC		=	gcc
RM		=	rm -f
CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

$(NAME):	$(OBJS) $(HEADERS)
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo -- Library created --

all:		$(NAME)

bonus:		$(NAME)

clean:
			@$(RM) $(OBJS)
			@echo -- Object files cleared --

fclean:
			@$(RM) $(OBJS) $(NAME)
			@echo -- Full clear acomplished --

re:			fclean all

.PHONY:		all clean fclean re