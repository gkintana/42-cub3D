/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:56:22 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/05 21:33:47 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	convert_hex_to_int(int r, int g, int b)
{
	return ((int)(((r / 16) * pow(16, 5))
			+ ((r % 16) * pow(16, 4))
			+ ((g / 16) * pow(16, 3))
			+ ((g % 16) * pow(16, 2))
			+ ((b / 16) * pow(16, 1))
			+ ((b % 16) * pow(16, 0))));
}

// https://stackoverflow.com/questions/20297594/warning-expected-int-but-argume
// nt-is-of-type-int-sizetypen
/*
** transfers each individual pixel from the pre-rendered texture buffer to the
** output image's address. Used for textured raycasting
** 
** i[0] = index for y-axis of map
** i[1] = index for x-axis of map
*/
void	draw_walls(t_program *prog, int (*buffer)[prog->mlx.win_width])
{
	int	i[2];

	int	j[6];
	j[0] = prog->tex.rgb.floor_r;
	while (j[0] % 5 != 0 && j[0] > 0)
		j[0]--;
	j[1] = prog->tex.rgb.floor_g;
	while (j[1] % 5 != 0 && j[1] > 0)
		j[1]--;
	j[2] = prog->tex.rgb.floor_b;
	while (j[2] % 5 != 0 && j[2] > 0)
		j[2]--;
	j[3] = prog->tex.rgb.ceiling_r;
	while (j[3] % 5 != 0 && j[3] > 0)
		j[3]--;
	j[4] = prog->tex.rgb.ceiling_g;
	while (j[4] % 5 != 0 && j[4] > 0)
		j[4]--;
	j[5] = prog->tex.rgb.ceiling_b;
	while (j[5] % 5 != 0 && j[5] > 0)
		j[5]--;
	
	int	floor = convert_hex_to_int(j[0], j[1], j[2]);
	int	ceiling = convert_hex_to_int(j[3], j[4], j[5]);
	
	
	i[0] = -1;
	while (++i[0] < prog->mlx.win_height)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width)
		{
			if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.850 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.rgb.ceiling);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.875 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					ceiling * 0.8);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.900 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					ceiling * 0.6);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.925 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					ceiling * 0.4);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.950 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					ceiling * 0.2);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.975 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					ceiling * 0.0);
					
			
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.150 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.rgb.floor);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.125 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					floor * 0.8);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.100 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					floor * 0.6);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.075 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					floor * 0.4);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.050 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					floor * 0.2);


			// if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 + prog->info.pitch)
			// 	put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
			// 		prog->tex.rgb.ceiling);
			// else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 + prog->info.pitch)
			// 	put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
			// 		prog->tex.rgb.floor);
			else
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					buffer[i[0]][i[1]]);
		}
	}
}

/*
** draws a simple line which assists the player in visualizing which direction
** they're currently facing
**
** i[0] = offset from player cube's center
** i[1] = calculations for the x-coordinate of a point representing the player's
**        perspective at i[0]'s distance
** i[2] = calculations for the y-coordinate of a point representing the player's
**        perspective at i[0]'s distance
*/
void	draw_player_perspective(t_program *prog)
{
	int	i[3];

	ft_bzero(&i, sizeof(int) * 3);
	i[0] = 5;
	while (++i[0] < 15)
	{
		i[1] = prog->info.vec_x * i[0] + prog->mlx.win_width / prog->map.scale
			* 7 + prog->map.offset_x + 0.5;
		i[2] = prog->info.vec_y * i[0] + prog->mlx.win_height / prog->map.scale
			* 7 + prog->map.offset_y / 2 + 1;
		put_pixel_at_addr(&prog->mlx.img[0], i[1], i[2], 0xFFFF00);
	}
}

/*
** provides an estimate of the player's location based on the current block
** they're standing on
**
** i[0] = player cube size
** i[1] = player's y-axis
** i[2] = player's x-axis
** i[3] = player's current x-coordinate after scaling
** i[4] = player's current y-coordinate after scaling
*/
void	draw_player(t_program *prog)
{
	int	i[5];

	i[0] = 6;
	i[1] = -1;
	while (++i[1] < i[0])
	{
		i[2] = -1;
		i[3] = 0;
		i[4] = 0;
		while (++i[2] < i[0])
		{
			i[3] = i[2] + prog->mlx.win_width / prog->map.scale
				* 7 + prog->mlx.win_width / prog->map.scale / 2 - (i[0] / 2);
			i[4] = i[1] + prog->mlx.win_height / prog->map.scale
				* 7 + prog->mlx.win_height / prog->map.scale / 2 - (i[0] / 2);
			put_pixel_at_addr(&prog->mlx.img[0], i[3], i[4], 0xFF0000);
		}
	}
	draw_player_perspective(prog);
}
