cmake_minimum_required(VERSION 3.17)
project(Cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(Cub3D
        control/cub_control.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        images/game.c
        images/image_utils.c
        includes/cub3d.h
        includes/cub_control.h
        includes/cub_image.h
        includes/cub_parser.h
        includes/cub_utils.h
        includes/get_next_line.h
        includes/libft.h
        includes/mlx.h
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd_back.c
        libft/ft_lstadd_front.c
        libft/ft_lstclear.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstlast.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_lstsize.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr_fd.c
        libft/ft_split.c
        libft/ft_strchr.c
        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strmapi.c
        libft/ft_strncmp.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strtrim.c
        libft/ft_substr.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        parser/cub_parser.c
        parser/map_parser.c
        parser/resolution_parser.c
        parser/settings_parser.c
        parser/texture_and_color_parser.c
        utils/cub_errors.c
        utils/cub_str_utils.c
        utils/cub_utils.c
        utils/cub_utils2.c
        cub3d.c)
target_link_libraries(Cub3D /Users/pkentaur/CLionProjects/Cub3D/libmlx.a)
target_link_libraries(Cub3D "-framework OpenGL")
target_link_libraries(Cub3D "-framework AppKit")
#add_definitions(-Wall -Wextra -Werror)