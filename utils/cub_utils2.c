/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkentaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:35:31 by pkentaur          #+#    #+#             */
/*   Updated: 2020/12/22 16:35:33 by pkentaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_utils.h"

void	check_err(int *i, char *line)
{
	int	k;

	k = *i;
	while (line[k] == ' ')
		++k;
	if (line[k] == '\0')
		print_error("Invalid cub settings");
}
