/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:58:32 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/07 14:00:33 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
** draws a large black box on the screen which will serve as the background of
** our minimap
**
** i[0] = index for minimap background's y-axis
** i[1] = index for minimap background's x-axis
*/
static void	draw_map_box(t_program *prog)
{
	int	i[2];

	ft_bzero(&i, sizeof(int) * 2);
	i[0] = prog->mlx.win_height / prog->map.scale - 2;
	while (++i[0] < prog->mlx.win_height / prog->map.scale * 14)
	{
		i[1] = prog->mlx.win_width / prog->map.scale - 2;
		while (++i[1] < prog->mlx.win_width / prog->map.scale * 14)
			put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0], 0x000000);
	}
}

/*
** draws a block of a specific color to our prog->mlx.img[0] based on the
** coordinates set at the x and y parameters
**
** i[0] = pixel position with respect to the block's y-axis
** i[1] = pixel position with respect to the block's x-axis
** i[2] = pixel position + x-offset
** i[3] = pixel position + y-offset
*/
static void	draw_block(t_program *prog, int x, int y, int color)
{
	int	i[4];

	i[0] = -1;
	while (++i[0] < prog->mlx.win_height / prog->map.scale - 1)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width / prog->map.scale - 1)
		{
			i[2] = i[1] + prog->mlx.win_width / prog->map.scale + x;
			i[3] = i[0] + prog->mlx.win_height / prog->map.scale + y;
			put_pixel_at_addr(&prog->mlx.img[0], i[2], i[3], color);
		}
	}
}

/*
** counts then returns the total number of elements in the prog->mlx.map[][]
** array
*/
static int	get_map_height(t_program *prog)
{
	int	height;

	height = 0;
	while (prog->mlx.map[height])
		height++;
	return (height);
}

int	find_wall_start(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '1')
			return (i);
	}
	return (0);
}

int	is_valid_coordinate(t_program *prog, int j[])
{
	if (j[0] >= 0 && j[0] < get_map_height(prog)
	&& j[1] >= 0 && j[1] < (int)ft_strlen(prog->mlx.map[j[0]]))
		return (1);
	return (0);
}

int check_north_wall(t_program *prog, int j[])
{
	int	x;
	int	y;

	x = j[1];
	y = j[0];
	while (--y > 0)
	{
		if (is_valid_coordinate(prog, j) && (prog->mlx.map[y][x] == '1'))
			return (1);
		else if (is_valid_coordinate(prog, j) && (prog->mlx.map[y][x] == '0'))
			break ;
	}
	return (0);
}

int	check_south_wall(t_program *prog, int j[])
{
	int	x;
	int	y;

	x = j[1];
	y = j[0];
	while (prog->mlx.map[++y])
	{
		if (!ft_strchr(prog->mlx.map[y], '0') && y == get_map_height(prog) - 1)
			return (1);
		if (is_valid_coordinate(prog, j) && (prog->mlx.map[y][x] == '1'))
			return (1);
		else if (is_valid_coordinate(prog, j) && (prog->mlx.map[y][x] == '0'))
			break ;
	}
	return (0);
}

int check_east_wall(char *str, int j)
{
	while (str[++j])
	{
		if (str[j] == '1')
			return (1);
		else if (str[j] == '0')
			break;
	}
	return (0);
}

int	check_west_wall(char *str, int j)
{
	while (--j > 0)
	{
		if (str[j] == '1')
			return (1);
		else if (str[j] == '0')
			break;
	}
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

/*
** checks if the values being used when accessing prog->mlx.map are within the
** limits of the allocation
**
** When checking prog->mlx.map[] we have to ensure that the value of the 
** variable is less than or equal to zero, and less than the map's total height.
** When checking prog->mlx.map[][] we test if the value of the variable is less
** than or equal to zero, and less than the current map line's length
**
** j[0] = stores the result of player's y-position + current y-block
** j[1] = stores the result of player's x-position + current x-block
*/
static int	check_map_coordinates(t_program *prog, int i[], bool is_wall,
			bool is_space)
{
	int	j[2];

	j[0] = (int)prog->info.pos_y + i[0];
	j[1] = (int)prog->info.pos_x + i[2];
	if (is_wall)
	{
		if (is_valid_coordinate(prog, j) && prog->mlx.map[j[0]][j[1]] == '1')
			return (1);
	}
	else if (is_space)
	{
		if (is_valid_coordinate(prog, j) && prog->mlx.map[j[0]][j[1]] == ' '
		&& j[1] < find_wall_start(prog->mlx.map[j[0]]))
			return (1);
		else if (is_valid_coordinate(prog, j) && prog->mlx.map[j[0]][j[1]] == ' '
		&& space_is_inside(prog, j))
			return (1);
	}
	else
	{
		if (is_valid_coordinate(prog, j)
		&& ft_strchr(" 0NSEW", prog->mlx.map[j[0]][j[1]]))
			return (1);
	}
	return (0);
}

/*
** draws the minimap to the top left corner of our prog->mlx.img[0]
**
** i[0] = current y-block
** i[1] = offset value that will be multiplied to block height
** i[2] = current x-block
** i[3] = offset value that will be multiplied to block width
** i[4] = result of i[3] * block width
** i[5] = result of i[1] * block height
*/
void	draw_map(t_program *prog)
{
	int	i[6];

	draw_map_box(prog);
	ft_bzero(&i, sizeof(int) * 6);
	i[0] = -7;
	i[1] = 0;
	while (++i[0] < 7)
	{
		i[2] = -7;
		i[3] = 0;
		while (++i[2] < 7)
		{
			i[4] = i[3] * prog->mlx.win_width / prog->map.scale;
			i[5] = i[1] * prog->mlx.win_height / prog->map.scale;
			if (check_map_coordinates(prog, i, true, false))
				draw_block(prog, i[4], i[5], 0x3313294B);
			else if (check_map_coordinates(prog, i, false, true))
				draw_block(prog, i[4], i[5], 0x000000);
			else if (check_map_coordinates(prog, i, false, false))
				draw_block(prog, i[4], i[5], 0x33777777);
			i[3]++;
		}
		i[1]++;
	}
}
