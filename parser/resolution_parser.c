/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:07:46 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 16:08:25 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_parser.h"
#include "cub_utils.h"

static void	add_resolution(t_parser *parser, char *width, char *height)
{
	parser->res_x = ft_atoi(width);
	parser->res_y = ft_atoi(height);
	if (parser->res_x > 2560)
		parser->res_x = 2560;
	else if (parser->res_x < 10)
		parser->res_x = 10;
	if (parser->res_y > 1440)
		parser->res_y = 1440;
	else if (parser->res_y < 10)
		parser->res_y = 10;
}

static void	if_nflag(int *j, int *i, char *line, char width[])
{
	while (ft_isdigit(line[*i]))
	{
		if (*j > 9)
		{
			width[0] = '9';
			width[1] = '9';
			width[2] = '9';
			width[3] = '9';
			width[4] = '\0';
			while (line[*i] != ' ' && line[*i] != '\0')
				++(*i);
			check_err(i, line);
			return ;
		}
		width[(*j)++] = line[(*i)++];
	}
	width[*j] = '\0';
	check_err(i, line);
}

static void	if_flag(int *j, int *i, char *line, char height[])
{
	while (ft_isdigit(line[*i]))
	{
		if (*j > 9)
		{
			height[0] = '9';
			height[1] = '9';
			height[2] = '9';
			height[3] = '9';
			height[4] = '\0';
			while (line[*i] != ' ' && line[*i] != '\0')
				++(*i);
			return ;
		}
		height[(*j)++] = line[(*i)++];
	}
	height[*j] = '\0';
}

static void	skip_spcs_chck_err(int *i, char *line, int flag)
{
	*i = skip_spaces(line, *i);
	if (!ft_isdigit(line[*i]) || flag > 1)
		print_error("Invalid cub settings");
}

void		parse_resolution(char *line, t_parser *parser, int i)
{
	char	width[10];
	char	height[10];
	int		j;
	int		wherr_flag;

	j = 0;
	wherr_flag = 0;
	++i;
	while (line[i])
	{
		skip_spcs_chck_err(&i, line, wherr_flag);
		if (wherr_flag == 0)
		{
			if_nflag(&j, &i, line, width);
			++wherr_flag;
		}
		else if (wherr_flag == 1)
		{
			j = 0;
			if_flag(&j, &i, line, height);
			++wherr_flag;
		}
		i = skip_spaces(line, i);
	}
	add_resolution(parser, width, height);
}
