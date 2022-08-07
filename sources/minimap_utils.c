/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:03:49 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/07 14:06:33 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
** counts then returns the total number of elements in the prog->mlx.map[][]
** array
*/
int	get_map_height(t_program *prog)
{
	int	height;

	height = 0;
	while (prog->mlx.map[height])
		height++;
	return (height);
}

int	find_wall_start(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '1')
			return (i);
	return (0);
}

int	is_valid_coordinate(t_program *prog, int j[])
{
	if (j[0] >= 0 && j[0] < get_map_height(prog)
	&& j[1] >= 0 && j[1] < (int)ft_strlen(prog->mlx.map[j[0]]))
		return (1);
	return (0);
}