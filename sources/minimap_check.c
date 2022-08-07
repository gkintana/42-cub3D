/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 14:03:51 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/07 16:49:33 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	check_north_wall(t_program *prog, int j[])
{
	int	x;
	int	y;

	x = j[1];
	y = j[0];
	while (--y > 0)
	{
		if ((prog->mlx.map[y][x] == '1'))
			return (1);
		// else if (is_valid_coordinate(prog, j) && (prog->mlx.map[y][x] == '0'))
		// 	break ;
	}
	if (prog->mlx.map[0][x] == '1')
		return (1);
	return (0);
}

static int	check_south_wall(t_program *prog, int j[])
{
	int	x;
	int	y;

	x = j[1];
	y = j[0];
	// if (!ft_strchr(prog->mlx.map[y], '0') && y == get_map_height(prog) - 1)
	// 	return (0);
	while (prog->mlx.map[++y])
	{
		// if (!ft_strchr(prog->mlx.map[y], '0') && y == get_map_height(prog) - 1)
		// 	return (0);
		if ((prog->mlx.map[y][x] == '1'))
			return (1);
		// else if (is_valid_coordinate(prog, j) && (prog->mlx.map[y][x] == '0'))
		// 	break ;
	}
	// if (!prog->mlx.map[y])
	// 	return (-1);
	return (0);
}

static int	check_east_wall(char *str, int j)
{
	while (str[++j])
	{
		if (str[j] == '1')
			return (1);
		// else if (str[j] == '0')
		// 	break;
	}
	return (0);
}

static int	check_west_wall(char *str, int j)
{
	while (--j > 0)
	{
		if (str[j] == '1')
			return (1);
		// else if (str[j] == '0')
		// 	break;
	}
	if (str[0] == '1')
		return (1);
	return (0);
}

int	space_is_inside(t_program *prog, int j[])
{
	if (j[1] > find_wall_start(prog->mlx.map[j[0]])
		&& check_north_wall(prog, j)
		&& check_south_wall(prog, j)
		&& check_east_wall(prog->mlx.map[j[0]], j[1])
		&& check_west_wall(prog->mlx.map[j[0]], j[1]))
		return (1);
	return (0);
}