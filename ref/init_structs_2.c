/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoro <mgregoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:53:35 by myael             #+#    #+#             */
/*   Updated: 2022/06/07 14:31:51 by mgregoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_direction_vector_2(char direction, t_all *all)
{
	if (direction == 'S')
	{
		all->player->dir_x = 0;
		all->player->dir_y = 1;
		all->plane->plane_x = 0.66;
		all->plane->plane_y = 0;
	}
	else if (direction == 'N')
	{
		all->player->dir_x = 0;
		all->player->dir_y = -1;
		all->plane->plane_x = -0.66;
		all->plane->plane_y = 0;
	}
}

void	fill_direction_vector(char direction, t_all *all)
{
	if (direction == 'W')
	{
		all->player->dir_x = -1;
		all->player->dir_y = 0;
		all->plane->plane_x = 0;
		all->plane->plane_y = 0.66;
	}
	else if (direction == 'E')
	{
		all->player->dir_x = 1;
		all->player->dir_y = 0;
		all->plane->plane_x = 0;
		all->plane->plane_y = -0.66;
	}
	else if (direction == 'S' || direction == 'N')
		fill_direction_vector_2(direction, all);
}

void	add_player_to_struct(t_all *all, int i, int j, char direction)
{
	t_player	*player;
	t_plane		*plane;

	player = malloc(sizeof(t_player));
	plane = malloc(sizeof(t_plane));
	all->plane = plane;
	player->pos_x = j + 0.5;
	player->pos_y = i + 0.5;
	all->m->map[i][j] = '0';
	all->player = player;
	fill_direction_vector(direction, all);
}
