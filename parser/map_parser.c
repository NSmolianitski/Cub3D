#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"
#include "cub_parser.h"
#include "cub_utils.h"

static int	are_walls_valid(char **map, int i, int j, t_map_size map_size)
{
	if (map[i][j] != '1' && map[i][j] != ' ')
	{
		if (i == 0 || i == map_size.y || j == 0 || j == map_size.x)
			return (0);
		else
		{

			if ((map[i][j + 1] == ' ' || map[i][j - 1] == ' ') ||
				(map[i - 1][j] == ' ' || map[i + 1][j] == ' '))
				return (0);
		}
	}
	return (1);
}

static int	check_player_pos(char **map, t_parser *parser, int i, int j)
{
	if (ft_strchr("NSWE", map[i][j]))
	{
		if (parser->player_dir != '0')
			return (0);
		parser->player_dir = map[i][j];
		parser->player_pos.y = i;
		parser->player_pos.x = j;
	}
	return (1);
}

static int	check_map(char **map, t_map_size map_size, t_parser *parser)
{
	int		i;
	int		j;

	i = -1;
	parser->player_dir = '0';
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!check_player_pos(map, parser, i, j))
				print_error("Zero or more than one player");
			if (!ft_strchr("012NSWE ", map[i][j]))
				print_error("Not a valid map symbol");
			if (!are_walls_valid(map, i, j, map_size))
				print_error("The map is not surrounded by walls");
		}
	}
	if (parser->player_dir == '0')
		print_error("Zero or more than one player");
	return (1);
}

static char		**map_to_arr(t_list *lst_begin, t_parser *parser)
{
	char		**map;
	int			i;
	t_map_size	map_size;

	map_size.y = ft_lstsize(lst_begin);
	map = ft_calloc( map_size.y + 1, sizeof(char *));
	if (!map)
		print_error("Malloc returned NULL");
	i = 0;
	map_size.x = lst_find_longest(lst_begin);
	while (lst_begin)
	{
		map[i] = s_calloc(map_size.x, sizeof(char), ' ');
		cub_strcpy(map[i], lst_begin->content);
		lst_begin = lst_begin->next;
		++i;
	}
	if (!check_map(map, map_size, parser))
		return (NULL);
	return (map);
}

void			map_parsing(t_parser *parser)
{
	t_list	*lst_begin;
	char	*line;
	int 	fd;
	char	**map;

	lst_begin = NULL;
	fd = open("../cubs/cube_map.cub", O_RDONLY);
	while (get_next_line(fd, &line))
		ft_lstadd_back(&lst_begin, ft_lstnew(line));
	ft_lstadd_back(&lst_begin, ft_lstnew(line));
	map = map_to_arr(lst_begin, parser);
	ft_lstclear(&lst_begin, free);
	close(fd);
	parser->map = map;
}