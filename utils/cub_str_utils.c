#include <unistd.h>
#include "libft.h"

int		cub_strcmp(const char *s1, const char *s2)
{
	unsigned int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			if ((((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]) > 0)
				return (1);
			else
				return (-1);
		}
		++i;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}

void	strprint(const char *str, int output)
{
	write(output, str, ft_strlen(str));
}

int	skip_spaces(const char *line, int i)
{
	while (line[i] == ' ')
		++i;
	return (i);
}

int	skip_spaces_and_commas(const char *line, int i)
{
	while (line[i] == ' ' || line[i] == ',')
		++i;
	return (i);
}