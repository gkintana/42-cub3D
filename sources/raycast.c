/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:55:41 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/10 14:56:06 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	raycast_loop(t_program *prog)
{
	t_calculations	calc;
	t_raycast		ray;
	int	i;

	ft_bzero(&calc, sizeof(t_calculations));
	ft_bzero(&ray, sizeof(t_raycast));
	i = -1;
	while (++i < prog->mlx.win_width)
	{
		calc.camera = 2 * i / (double)prog->mlx.win_width - 1;
		calc.ray_vec_x = prog->info.vec_x + prog->info.plane_x * calc.camera;
		calc.ray_vec_y = prog->info.vec_y + prog->info.plane_y * calc.camera;
		calc.delta_x = fabs(1 / calc.ray_vec_x);
		calc.delta_y = fabs(1 / calc.ray_vec_y);
		calc.map_x = (int)prog->info.pos_x;
		calc.map_y = (int)prog->info.pos_y;
		
		
		if (calc.ray_vec_x < 0)
		{
			calc.offset_x = -1;
			calc.side_dist_x = (prog->info.pos_x - calc.map_x) * calc.delta_x;
		}
		else
		{
			calc.offset_x = 1;
			calc.side_dist_x = (calc.map_x + 1.0 - prog->info.pos_x) * calc.delta_x;
		}
		if (calc.ray_vec_y < 0)
		{
			calc.offset_y = -1;
			calc.side_dist_y = (prog->info.pos_y - calc.map_y) * calc.delta_y;
		}
		else
		{
			calc.offset_y = 1;
			calc.side_dist_y = (calc.map_y + 1.0 - prog->info.pos_y) * calc.delta_y;
		}

		
		while (true)
		{
			if (calc.side_dist_x < calc.side_dist_y)
			{
				calc.side_dist_x += calc.delta_x;
				calc.map_x += calc.offset_x;
				calc.side = 0;
			}
			else
			{
				calc.side_dist_y += calc.delta_y;
				calc.map_y += calc.offset_y;
				calc.side = 1;
			}
			if (prog->mlx.map[calc.map_y][calc.map_x] == '1')
				break ;
		}


		if (!calc.side)
			calc.perp_dist = calc.side_dist_x - calc.delta_x;
		else
			calc.perp_dist = calc.side_dist_y - calc.delta_y;


		ray.line_height = (int)(prog->mlx.win_height / calc.perp_dist);
		ray.start = -ray.line_height / 2 + prog->mlx.win_height / 2;
		if (ray.start < 0)
			ray.start = 0;
		ray.end = ray.line_height / 2 + prog->mlx.win_height / 2;
		if (ray.end >= prog->mlx.win_height)
			ray.end = prog->mlx.win_height - 1;
			
		if (!calc.side)
			ray.wall = prog->info.pos_y + calc.perp_dist * calc.ray_vec_y;
		else
			ray.wall = prog->info.pos_x + calc.perp_dist * calc.ray_vec_x;
		ray.wall -= floor(ray.wall);

		ray.texture_x = (int)(ray.wall * (double)prog->tex.width);
		if (!calc.side && calc.ray_vec_x > 0)
			ray.texture_x = prog->tex.width - ray.texture_x - 1;
		else if (calc.side && calc.ray_vec_y < 0)
			ray.texture_x = prog->tex.width - ray.texture_x - 1;

		ray.step = 1.0 * prog->tex.height / ray.line_height;
		ray.texture_pos = (ray.start - prog->mlx.win_height / 2 + ray.line_height / 2) * ray.step;


		int	j;

		j = ray.start;
		while (j < ray.end)
		{
			ray.texture_y = (int)ray.texture_pos & (prog->tex.height - 1);
			ray.texture_pos += ray.step;
			ray.color = prog->mlx.img[1].pixel[prog->tex.height * ray.texture_y + ray.texture_x];
			if (calc.side)
				ray.color = (ray.color >> 1) & 8355711;
			ray.buffer[j][i] = ray.color;
			j++;
		}


		// int	color = 0xFFFFFF;
		// if (data->map[map_y][map_x] == '1')
		// 	color = 0xAA0000;
		// if (side)
		// 	color /= 2;
		// draw_line(&data->img[0], x, draw_start, draw_end, color);
	}
	draw_walls(prog, ray.buffer);
	draw_map(prog);
	draw_player(prog);
	mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window, prog->mlx.img[0].ptr, 0, 0);
	return (0);
}