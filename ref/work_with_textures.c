/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoro <mgregoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:41:01 by myael             #+#    #+#             */
/*   Updated: 2022/06/07 14:32:05 by mgregoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_to_xpm_data_my(t_win *win, char *path, t_win *data)
{
	data->img = mlx_xpm_file_to_image(win->mlx, path, &data->x, &data->y);
	check_malloc_err(data->img, "couldn't alloc texture img", 21);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
			&data->l_len, &data->end);
	check_malloc_err(data->addr, "couldn't alloc texture addr", 22);
}

unsigned int	get_tex_color_pixel(t_win *img, int x, int y)
{
	int	*dst;
	int	color;

	dst = (void *)img->addr + (y * img->l_len + x * (img->bpp / 8));
	color = *(int *)dst;
	return (color);
}

int	add_shade(double distance, int color)
{
	int		transparency;
	int		red;
	int		green;
	int		blue;

	transparency = color & 0xFF000000;
	red = color & 0x00FF0000;
	green = color & 0x0000FF00;
	blue = color & 0x000000FF;
	red = (red >> 16) * (1 - distance);
	green = (green >> 8) * (1 - distance);
	blue = blue * (1 - distance);
	red = red << 16;
	green = green << 8;
	return (transparency | red | green | blue);
}

void	draw_texture(t_all *all, t_win *tex, int x, int shade)
{
	int	y;

	y = all->rc->draw_start;
	all->rc->tex_x = (int)(all->rc->wall_x * (double)(tex->x));
	if (all->rc->side == 0 && all->rc->ray_dir_x > 0)
		all->rc->tex_x = tex->x - all->rc->tex_x - 1;
	if (all->rc->side == 1 && all->rc->ray_dir_y < 0)
		all->rc->tex_x = tex->x - all->rc->tex_x - 1;
	all->rc->step = 1.0 * tex->y / all->rc->line_height;
	all->rc->tex_pos = (all->rc->draw_start - HEIGHT / 2 + \
			all->rc->line_height / 2) * all->rc->step;
	while (y < all->rc->draw_end)
	{
		all->rc->tex_y = (int)all->rc->tex_pos & (tex->y - 1);
		all->rc->tex_pos += all->rc->step;
		all->rc->color = get_tex_color_pixel(tex, \
			all->rc->tex_x, all->rc->tex_y);
		if (shade == 0)
			my_mlx_pixel_put(all->win, x, y, all->rc->color);
		else
			my_mlx_pixel_put(all->win, x, y, add_shade(0.2, all->rc->color));
		++y;
	}
}

void	draw_textures_on_walls(t_all *all, int x)
{
	if (all->rc->side == 1 && all->rc->step_y < 0)
		draw_texture(all, all->n_tex, x, 1);
	else if (all->rc->side == 1 && all->rc->step_y > 0)
		draw_texture(all, all->s_tex, x, 0);
	else if (all->rc->side == 0 && all->rc->step_x < 0)
		draw_texture(all, all->e_tex, x, 1);
	else if (all->rc->side == 0 && all->rc->step_x > 0)
		draw_texture(all, all->w_tex, x, 0);
}
