/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:56:22 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/01 18:28:17 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

	i[0] = -1;
	while (++i[0] < prog->mlx.win_height)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width)
		{
			
			if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.850 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.875 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb * 0.8);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.900 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb * 0.6);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.925 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb * 0.4);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.950 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb * 0.2);
			else if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 * 0.975 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb * 0.0);

			
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.150 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.floor_rgb);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.125 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.floor_rgb * 0.8);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.100 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.floor_rgb * 0.6);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.075 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.floor_rgb * 0.4);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 * 1.050 + prog->info.pitch)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.floor_rgb * 0.2);



			// if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2 + prog->info.pitch)
			// 	put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
			// 		prog->tex.ceiling_rgb);
			// else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2 + prog->info.pitch)
			// 	put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
			// 		prog->tex.floor_rgb);
			else
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					buffer[i[0]][i[1]]);
		}
	}
}

/*
 * draws the minimap on our image pointer, specifically at the coordinates set
 * at prog.map.offset_x and prog.map.offset_y
 * 
 * i[0] = index for the y-axis of prog->mlx.map
 * i[1] = index for the x-axis of prog->mlx.map
 * i[2] = index for the y-axis of the minimap's image
 * i[3] = index for the x-axis of the minimap's image
 * 
 * decided to put each pixel individually on the image before printing it to
 * the window because when I ran the program through valgrind while using the
 * mlx_put_image_to_window function in a loop, it was extremely slow and had
 * a 700,000+ bytes leak at exit.
 * 
 * This approach while not perfect nor efficient, reduced the cpu load and
 * memory usage by a large margin
 */
void	draw_map(t_program *prog)
{
	int	i[4];

	i[0] = -1;
	while (prog->mlx.map[++i[0]])
	{
		i[1] = -1;
		while (prog->mlx.map[i[0]][++i[1]])
		{
			if (prog->mlx.map[i[0]][i[1]] != ' ' && prog->mlx.map[i[0]][i[1]] != '\n')
			{
				i[2] = -1;
				while (++i[2] < prog->mlx.win_height / prog->map.scale)
				{
					i[3] = -1;
					while (++i[3] < prog->mlx.win_width / prog->map.scale)
						put_pixel_at_addr(&prog->mlx.img[0],
						i[3] + prog->mlx.win_width / prog->map.scale * i[1] + prog->map.offset_x,
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0x000000);
				}
			}
		}
	}

	i[0] = -1;
	// i[0] = prog->info.pos_y - 5;
	// if (i[0] < 0)
	// 	i[0] = -1;
	while (prog->mlx.map[++i[0]])
	{
		i[1] = -1;
		// i[1] = prog->info.pos_x - 5;
		// if (i[1] < 0)
		// 	i[1] = -1;
		while (prog->mlx.map[i[0]][++i[1]])
		{
			// if (prog->mlx.map[i[0]][i[1]] == '1' && i[1] < prog->info.pos_x + 5 && i[0] < prog->info.pos_y + 5)
			if (prog->mlx.map[i[0]][i[1]] == '1')
			{
				i[2] = -1;
				while (++i[2] < prog->mlx.win_height / prog->map.scale - 1)
				{
					i[3] = -1;
					while (++i[3] < prog->mlx.win_width / prog->map.scale - 1)
						put_pixel_at_addr(&prog->mlx.img[0],
						i[3] + prog->mlx.win_width / prog->map.scale * i[1] + prog->map.offset_x,
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0x3313294B);
				}
				// for (int k = 0; k < data->win_height / 100; k++) {
				// 	for (int j = 0; j < data->win_width / 100; j++) {
				// 		put_pixel_at_addr(&data->img[0], j + data->win_width / 100 * i[1] + 15,
				// 		k + data->win_height / 100 * i[0] + 15, 0xAA555555);
				// 	}
				// }
				// mlx_put_image_to_window(data->mlx, data->mlx_window, data->img[2].ptr,
				// i[1] * data->win_width / 100 + 25, i[0] * data->win_height / 100 + 25);
			}
			// else if (prog->mlx.map[i[0]][i[1]] != '1' && !ft_isspace(prog->mlx.map[i[0]][i[1]]) && i[1] < prog->info.pos_x + 5 && i[0] < prog->info.pos_y + 5)
			else if (prog->mlx.map[i[0]][i[1]] != '1' && !ft_isspace(prog->mlx.map[i[0]][i[1]]))
			{
				i[2] = -1;
				while (++i[2] < prog->mlx.win_height / prog->map.scale - 1)
				{
					i[3] = -1;
					while (++i[3] < prog->mlx.win_width / prog->map.scale - 1)
						put_pixel_at_addr(&prog->mlx.img[0],
						i[3] + prog->mlx.win_width / prog->map.scale * i[1] + prog->map.offset_x,
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0x33777777);
				}
			}
		}
	}
}

/*
** represents the player's location within the boundaries of the minimap
**
** Uses the same concept as the draw_map function in terms of pixels rather
** than relying on the mlx_put_image_to_window function
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

	i[0] = 4;
	i[1] = -1;
	while (++i[1] < i[0])
	{
		i[2] = -1;
		i[3] = 0;
		i[4] = 0;
		while (++i[2] < i[0])
		{
			i[3] = i[2] + prog->mlx.win_width / prog->map.scale
				* prog->info.pos_x + prog->map.offset_x - (i[0] / 2);
			i[4] = i[1] + prog->mlx.win_height / prog->map.scale
				* prog->info.pos_y + prog->map.offset_y - (i[0] / 2);
			put_pixel_at_addr(&prog->mlx.img[0], i[3], i[4], 0xFF0000);
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
			* prog->info.pos_x + prog->map.offset_x;
		i[2] = prog->info.vec_y * i[0] + prog->mlx.win_height / prog->map.scale
			* prog->info.pos_y + prog->map.offset_y;
		put_pixel_at_addr(&prog->mlx.img[0], i[1], i[2], 0xFFFF00);
	}
}
