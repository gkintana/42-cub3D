/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:56:22 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/30 12:44:39 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
 * draws a vertical line to our image's address according to the specified
 * starting and ending points. Used for untextured raycasting
 */
// void	draw_line(t_image *img, int x, int start, int end, int color)
// {
// 	int	i;

// 	i = start;
// 	while (++i < end)
// 		put_pixel_at_addr(&img[0], x, i, color);
// }

// https://stackoverflow.com/questions/20297594/warning-expected-int-but-argument-is-of-type-int-sizetypen
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
			if (!buffer[i[0]][i[1]] && i[0] < prog->mlx.win_height / 2)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.ceiling_rgb);
			else if (!buffer[i[0]][i[1]] && i[0] > prog->mlx.win_height / 2)
				put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0],
					prog->tex.floor_rgb);
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
			if (prog->mlx.map[i[0]][i[1]] == '1')
			{
				i[2] = -1;
				while (++i[2] < prog->mlx.win_height / prog->map.scale)
				{
					i[3] = -1;
					while (++i[3] < prog->mlx.win_width / prog->map.scale)
						put_pixel_at_addr(&prog->mlx.img[0],
						i[3] + prog->mlx.win_width / prog->map.scale * i[1] + prog->map.offset_x,
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0x33333333);
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
			else if (prog->mlx.map[i[0]][i[1]] != '1' && !ft_isspace(prog->mlx.map[i[0]][i[1]]))
			{
				i[2] = -1;
				while (++i[2] < prog->mlx.win_height / prog->map.scale)
				{
					i[3] = -1;
					while (++i[3] < prog->mlx.win_width / prog->map.scale)
						put_pixel_at_addr(&prog->mlx.img[0],
						i[3] + prog->mlx.win_width / prog->map.scale * i[1] + prog->map.offset_x,
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0x33555555);
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
** i[0] = player's y-axis
** i[1] = player's x-axis
** i[2] = player's current x-coordinate after scaling
** i[3] = player's current y-coordinate after scaling
*/
void	draw_player(t_program *prog)
{
	int	i[4];

	i[0] = -1;
	while (++i[0] < 3)
	{
		i[1] = -1;
		i[2] = 0;
		i[3] = 0;
		while (++i[1] < 3)
		{
			i[2] = i[1] + prog->info.pos_x * prog->mlx.win_width
				/ prog->map.scale + prog->map.offset_x;
			i[3] = i[0] + prog->info.pos_y * prog->mlx.win_height
				/ prog->map.scale + prog->map.offset_y;
			put_pixel_at_addr(&prog->mlx.img[0], i[2], i[3], 0xFF0000);
		}
	}
}
