/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myael <myael@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:43:44 by myael             #+#    #+#             */
/*   Updated: 2022/06/14 15:33:49 by myael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_floor_and_ceiling(t_all *all, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < all->rc->draw_start)
		{
			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->ceiling[0], \
					all->data->ceiling[1], all->data->ceiling[2]));
		}
		else if (y >= all->rc->draw_end)
		{
			my_mlx_pixel_put(all->win, x, y, create_rgb(all->data->floor[0], \
					all->data->floor[1], all->data->floor[2]));
		}
		++y;
	}
}

void	print_raycasted_map(int x, t_all *all)
{
	if (all->rc->side == 0)
	{
		all->rc->wall_x = all->player->pos_y + all->rc->perp_wall_dist * \
				all->rc->ray_dir_y;
	}
	else
	{
		all->rc->wall_x = all->player->pos_x + all->rc->perp_wall_dist * \
				all->rc->ray_dir_x;
	}
	all->rc->wall_x -= floor((all->rc->wall_x));
	draw_textures_on_walls(all, x);
	draw_floor_and_ceiling(all, x);
}

void	executing(t_all *all)
{
	all->win = malloc(sizeof(t_win));
	all->rc = malloc(sizeof(t_raycast));
	all->win->mlx = mlx_init();
	init_data_for_textures_and_speed(all);
	all->win->win = mlx_new_window(all->win->mlx, WIDTH, HEIGHT, "Cub3D");
	all->win->img = mlx_new_image(all->win->mlx, WIDTH, HEIGHT);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
			&all->win->l_len, &all->win->end);
	raycaster_start(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	mlx_do_key_autorepeaton(all->win->mlx);
	mlx_hook(all->win->win, 2, 0x1, key_hook, all);
	mlx_hook(all->win->win, 33, (1L << 17), close_win, all);
	mlx_loop(all->win->mlx);
}
