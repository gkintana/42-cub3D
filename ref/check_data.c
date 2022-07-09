/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:21:13 by myael             #+#    #+#             */
/*   Updated: 2022/06/14 15:02:25 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_spaces(t_all *all, char **map, int i, int j)
{
	if (check_if_symbol_is_zero_or_player(all, map, i, j - 1)
		|| check_if_symbol_is_zero_or_player(all, map, i, j + 1)
		|| check_if_symbol_is_zero_or_player(all, map, i + 1, j)
		|| check_if_symbol_is_zero_or_player(all, map, i - 1, j)
		|| check_if_symbol_is_zero_or_player(all, map, i + 1, j + 1)
		|| check_if_symbol_is_zero_or_player(all, map, i - 1, j + 1)
		|| check_if_symbol_is_zero_or_player(all, map, i + 1, j - 1)
		|| check_if_symbol_is_zero_or_player(all, map, i - 1, j - 1))
		error_exit("Zero symbol found in wrong place", 3);
}

void	check_line_for_spaces(t_all *all, char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != ' ')
		{
			if (all->checker->space_line == 1)
				error_exit("Space line inside the map", 4);
			return ;
		}
		j++;
	}
	all->checker->space_line = 1;
}

void	check_map_correctness(t_all *all)
{
	char		**map;
	int			i;
	int			j;

	i = -1;
	map = all->m->map;
	while (map[i] && (++i < all->m->height))
	{
		j = -1;
		check_line_for_spaces(all, map, i);
		while (map[i][++j] && j < all->m->width)
		{
			if (map[i][j] == ' ')
				check_spaces(all, map, i, j);
			else if (map[i][j] == '0')
				check_zeros_at_corners(all, i, j);
			else if (map[i][j] == '1')
				;
			else if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				check_one_player(all, map, i, j);
			else
				error_exit("Invalid symbol in map", 5);
		}
	}
}
