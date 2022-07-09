/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zeros_and_player.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:25:38 by myael             #+#    #+#             */
/*   Updated: 2022/06/14 15:03:32 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_if_map_has_player(t_all *all)
{
	if (all->checker->e == 0 && all->checker->w == 0
		&& all->checker->s == 0 && all->checker->n == 0)
		error_exit("Where is no player on the map", 12);
}

void	check_zeros_at_corners(t_all *all, int i, int j)
{
	if (i == 0 || i == all->m->height - 1 || j == 0 || j == all->m->width)
		error_exit("Zero is found in a corner. Wrong map", 13);
}

int	check_if_symbol_is_zero_or_player(t_all *all, char **map, int i, int j)
{
	return ((i >= 0 && i < all->m->height) && (j >= 0 && j < all->m->width)
		&& (map[i][j] == '0' || map[i][j] == 'N'
		|| map[i][j] == 'E' || map[i][j] == 'W'
		|| map[i][j] == 'S'));
}

int	check_if_symbol_is_zero(t_all *all, char **map, int i, int j)
{
	return ((i >= 0 && i < all->m->height)
		&& (j >= 0 && j < all->m->width) && map[i][j] == '0');
}

void	check_one_player(t_all *all, char **map, int i, int j)
{
	if (i == 0 || i == all->m->height)
		error_exit("Player in the wrong place", 14);
	if (map[i][j] == 'N' && all->checker->n == 0)
		all->checker->n++;
	else if (map[i][j] == 'E' && all->checker->e == 0)
		all->checker->e++;
	else if (map[i][j] == 'W' && all->checker->w == 0)
		all->checker->w++;
	else if (map[i][j] == 'S' && all->checker->s == 0)
		all->checker->s++;
	else
		error_exit("Something wrong with player", 15);
	if (all->checker->n + all->checker->e + all->checker->s
		+ all->checker->w > 1)
		error_exit("Something wrong with player", 15);
	if (!check_if_symbol_is_zero(all, map, i, j - 1)
		&& !check_if_symbol_is_zero(all, map, i, j + 1)
		&& !check_if_symbol_is_zero(all, map, i + 1, j)
		&& !check_if_symbol_is_zero(all, map, i - 1, j))
		error_exit("Player surrounded by walls. Wrong map", 16);
	add_player_to_struct(all, i, j, map[i][j]);
}
