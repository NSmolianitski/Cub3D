/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:33:53 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 15:35:46 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_parser.h"
#include "cub_image.h"
#include "cub_utils.h"

static void	check_settings(char **argv)
{
	int pl;

	pl = ft_strlen(argv[1]);
	if (!(argv[1][pl - 1] == 'b' && argv[1][pl - 2] ==
				'u' && argv[1][pl - 3] == 'c' && argv[1][pl - 4] == '.'))
		print_error("Invalid settings file format");
}

int			main(int argc, char **argv)
{
	t_parser		*parser;
	int				is_save;

	is_save = 0;
	if (argc < 2 || argc > 3)
		print_error("Wrong number of arguments");
	check_settings(argv);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7))
			print_error("Invalid cub argument");
		else
			is_save = 1;
	}
	parser = cub_parser(argv);
	game(parser, is_save);
	return (0);
}
