/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/10 14:48:43 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
 * draws a vertical line to our image's address according to the specified
 * starting and ending points. Used for untextured raycasting
 */
void	draw_line(t_image *img, int x, int start, int end, int color)
{
	int	i;

	i = start;
	while (++i < end)
		put_pixel_at_addr(&img[0], x, i, color);
}

// https://stackoverflow.com/questions/20297594/warning-expected-int-but-argument-is-of-type-int-sizetypen
/*
 * transfers each individual pixel from the pre-rendered texture buffer to the
 * output image's address. Used for textured raycasting
 * 
 * i[0] = index for y-axis of map
 * i[1] = index for x-axis of map
 */
void	draw_walls(t_program *prog, int (*buffer)[prog->mlx.win_width])
{
	int	i[2];

	i[0] = -1;
	while (++i[0] < prog->mlx.win_height)
	{
		i[1] = -1;
		while (++i[1] < prog->mlx.win_width)
			put_pixel_at_addr(&prog->mlx.img[0], i[1], i[0], buffer[i[0]][i[1]]);
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
	while(prog->mlx.map[++i[0]])
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
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0xAA333333);
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
						i[2] + prog->mlx.win_height / prog->map.scale * i[0] + prog->map.offset_y, 0xAA555555);
				}
			}
		}
	}
}

/*
 * represents the player's location within the boundaries of the minimap
 *
 * Uses the same concept as the draw_map function in terms of pixels rather
 * than relying on the mlx_put_image_to_window function
 */
void	draw_player(t_program *prog)
{
	int	i[2];

	i[0] = -1;
	while (++i[0] < 3)
	{
		i[1] = -1;
		while (++i[1] < 3)
			put_pixel_at_addr(&prog->mlx.img[0],
			i[1] + prog->info.pos_x * prog->mlx.win_width / prog->map.scale + prog->map.offset_x,
			i[0] + prog->info.pos_y * prog->mlx.win_height / prog->map.scale + prog->map.offset_y, 0xAAFF0000);
	}
	// mlx_put_image_to_window(data->mlx, data->mlx_window, data->img[3].ptr,
	// data->pos_x * data->win_width / 100 + 25 - 0.75, data->pos_y * data->win_height / 100 + 25 - 0.75);
}

int	raycast_loop(t_program *prog)
{
	// int buffer[data->win_height][data->win_width];
	// for (int i = 0; i < data->win_height; i++) {
	// 	for (int j = 0; j < data->win_width; j++) {
	// 		buffer[i][j] = 0;
	// 	}
	// }

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

		
		
	// }


	// for (int x = 0; x < data->win_width; x++) {
	// 	double	camera_x = 2 * x / (double)data->win_width - 1;
	// 	double	ray_dir_x = data->vec_x + data->plane_x * camera_x;
	// 	double	ray_dir_y = data->vec_y + data->plane_y * camera_x;
	// 	int	map_x = (int)data->pos_x;
	// 	int	map_y = (int)data->pos_y;
	// 	double	side_dist_x = 0;
	// 	double	side_dist_y = 0;
	// 	double	delta_dist_x = fabs(1 / ray_dir_x);
	// 	double	delta_dist_y = fabs(1 / ray_dir_y);
	// 	double	perp_dist = 0;
	// 	int	step_x = 0;
	// 	int	step_y = 0;
	// 	// int hit = 0;
	// 	int side = 0;
		
	// 	if (ray_dir_x < 0) {
	// 		step_x = -1;
	// 		side_dist_x = (data->pos_x - map_x) * delta_dist_x;
	// 	} else {
	// 		step_x = 1;
	// 		side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
	// 	}

	// 	if (ray_dir_y < 0) {
	// 		step_y = -1;
	// 		side_dist_y = (data->pos_y - map_y) * delta_dist_y;
	// 	} else {
	// 		step_y = 1;
	// 		side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
	// 	}

	// 	// DDA Algorithm
	// 	while (1) {
	// 		if (side_dist_x < side_dist_y) {
	// 			side_dist_x += delta_dist_x;
	// 			map_x += step_x;
	// 			side = 0;
	// 		} else {
	// 			side_dist_y += delta_dist_y;
	// 			map_y += step_y;
	// 			side = 1;
	// 		}
	// 		if (data->map[map_y][map_x] == '1')
	// 			break ;
	// 	}

	// 	if (!side)
	// 		perp_dist = side_dist_x - delta_dist_x;
	// 	else
	// 		perp_dist = side_dist_y - delta_dist_y;


		// int	line_height = (int)(data->win_height / calc.perp_dist);
		// int	draw_start = -line_height / 2 + data->win_height / 2;
		// if (draw_start < 0)
		// 	draw_start = 0;
		// int	draw_end = line_height / 2 + data->win_height / 2;
		// if (draw_end >= data->win_height)
		// 	draw_end = data->win_height - 1;


		// double wall_x;
		// if (!calc.side)
		// 	wall_x = data->pos_y + calc.perp_dist * calc.ray_vec_y;
		// else
		// 	wall_x = data->pos_x + calc.perp_dist * calc.ray_vec_x;
		// wall_x -= floor(wall_x);

		// int	texture_x = (int)(wall_x * (double)data->texture_width);
		// if (!calc.side && calc.ray_vec_x > 0)
		// 	texture_x = data->texture_width - texture_x - 1;
		// else if (calc.side && calc.ray_vec_y < 0)
		// 	texture_x = data->texture_width - texture_x - 1;

		// double step = 1.0 * data->texture_height / line_height;
		// double texture_pos = (draw_start - data->win_height / 2 + line_height / 2) * step;
		// for (int y = draw_start; y < draw_end; y++)
		// {
		// 	int	texture_y = (int)texture_pos & (data->texture_height - 1);
		// 	texture_pos += step;
		// 	int	color = data->img[1].pixel[data->texture_height * texture_y + texture_x];
		// 	if (calc.side)
		// 		color = (color >> 1) & 8355711;
		// 	buffer[y][i] = color;
		// }


		// ft_bzero(&ray, sizeof(t_raycast));
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

/*
 * parses the map and sets the player's starting location at the first
 * occurrence of a '0' character. Will be replaced later to the first
 * occurrence of any of the following characters "N or S or E or W"
 * 
 * i[0] = index for y-axis of map
 * i[1] = index for x-axis of map
 * i[2] = acts like a boolean to indicate if the player's starting
 *        location has been set
 */
void	set_player_position(t_program *prog)
{
	int	i[3];

	i[2] = 0;
	i[0] = -1;
	while (prog->mlx.map[++i[0]])
	{
		i[1] = -1;
		while (prog->mlx.map[i[0]][++i[1]])
		{
			if (prog->mlx.map[i[0]][i[1]] == '0')
			{
				prog->info.pos_x = i[1] + 0.50;
				prog->info.pos_y = i[0] + 0.50;
				i[2] = 1;
				break ;
			}
		}
		if (i[2])
			break ;
	}
}

int main(int argc, char **argv)
{
	t_program	prog;

	if (argc == 2) {
		ft_bzero(&prog, sizeof(t_program));
		prog.tex.north = "assets/multibrick.xpm";

		check_map_extension(argv[1]);
		prog.mlx.map = save_map(argv[1], check_map_validity(argv[1]));

		prog.mlx.ptr = mlx_init();
		prog.mlx.win_width = WIN_WIDTH;
		prog.mlx.win_height = WIN_HEIGHT;
		prog.mlx.window = mlx_new_window(prog.mlx.ptr, prog.mlx.win_width, prog.mlx.win_height, "cub3D");

		prog.mlx.img[0].ptr = mlx_new_image(prog.mlx.ptr, prog.mlx.win_width, prog.mlx.win_height);
		prog.mlx.img[0].addr = mlx_get_data_addr(prog.mlx.img[0].ptr, &prog.mlx.img[0].bpp, &prog.mlx.img[0].len, &prog.mlx.img[0].endian);
		// prog.tex.north is temporary
		prog.mlx.img[1].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.north, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[1].pixel = (int *)mlx_get_data_addr(prog.mlx.img[1].ptr, &prog.mlx.img[1].bpp, &prog.mlx.img[1].len, &prog.mlx.img[1].endian);

		set_player_position(&prog);
		prog.info.vec_x = 1;
		prog.info.vec_y = 0;
		prog.info.plane_x = 0;
		prog.info.plane_y = 0.66;
		prog.info.move_speed = 0.065;
		prog.info.rotate_speed = 0.035;

		prog.map.scale = 100;
		prog.map.offset_x = 15;
		prog.map.offset_y = 15;

		raycast_loop(&prog);
		mlx_hook(prog.mlx.window, 2, 1L<<0, key_events, &prog);
		mlx_loop(prog.mlx.ptr);
		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}