#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "cub_utils.h"

void	parse_color(char *line, int color[], int i)
{
	char	*num;
	int		j;
	int		num_start;

	++i;
	j = 0;
	while (j < 3)
	{
		i = skip_spaces_and_commas(line, i);
		num_start = i;
		while (ft_isdigit(line[i]))
			++i;
		num = ft_substr(line, num_start, i - num_start);
		color[j] = ft_atoi(num);
		free(num);
		++j;
	}
	if (line[i])
		print_error("Wrong floor or ceiling color");
}

void	parse_texture_path(char *line, char **tp, int i)
{
	int		path;
	int		path_len;
	char	*substr;
	int		fd;

	i = skip_spaces(line, i + 2);
	path = i;
	path_len = 0;
	while (line[i] != ' ' && line[i] != '\0')
	{
		++path_len;
		++i;
	}
	i = skip_spaces(line, i);
	if (line[i])
		print_error("Invalid cub settings");
	substr = ft_substr(line, path, path_len);
	*tp = ft_strdup(substr);
	fd = open(*tp, O_RDONLY);
	if (fd < 0 || ((*tp)[ft_strlen(*tp) - 1] != 'm' && (*tp)[ft_strlen(*tp) - 2] != 'p' && (*tp)[ft_strlen(*tp) - 3] != 'x' && (*tp)[ft_strlen(*tp) - 4] != '.'))
		print_error("Invalid texture path");
	else
		close(fd);
	free(substr);
}