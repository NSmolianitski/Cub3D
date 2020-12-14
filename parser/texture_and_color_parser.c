#include "libft.h"
#include "cub_utils.h"

void	parse_color(char *line, int color[], int i)
{
	char	*num;
	int 	j;
	int 	num_start;

	++i;
	j = 0;
	while(j < 3)
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

}

void	parse_texture_path(char *line, char **texture_path, int i)
{
	int		path;
	int 	path_len;
	char	*substr;

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
	*texture_path = ft_strdup(substr);
	free(substr);
}