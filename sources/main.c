/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/09 01:08:10 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
 * this function simply checks if the argument being passed is a file with a
 * .cub extension.
 * 
 * Note: will still work or sometimes even segfault when given invalid
 * 		 arguments
 */
void	check_map_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file) - 1;
	if (i >= 4 && file[i] == 'b' && file[i - 1] == 'u' && file[i - 2] == 'c' 
		&& file[i - 3] == '.')
		return ;
	ft_putstr_fd("Invalid Map Extension\n", 2);
	exit(1);
}

// int find_errors(char *line)
// {
	
// }

/*
 * function intended to parse map before proceding with the initializations,
 * calculations, raycasting, etc.
 */
int	check_map_validity(char *file)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error! Map file does not exist\n", 2);
		exit(1);
	}
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		// if (find_errors(str))
		// {
		// 	ft_putstr_fd("Invalid Map\n", 2);
		// 	exit(1);
		// }
		// printf("%s", str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	free(str);
	str = NULL;
	close(fd);
	return (i);
}

/*
 * saves the map in a 2d array if it passes the parser
 */
char	**save_map(char *file, int lines)
{
	char	**map;
	char	*temp;
	int		fd;
	int		i;

	map = (char **)ft_calloc(lines + 1, sizeof(char *));
	fd = open(file, O_RDONLY);
	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		map[i++] = ft_strdup(temp);
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	temp = NULL;
	close(fd);
	return (map);
}

void	free_2d_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/*
 * this is the my_mlx_pixel_put function from the minilibx documentation
 */
void	put_pixel_at_addr(t_img *img, int x, int y, int color)
{
	char			*pixel;
	unsigned int	pixel_position;

	pixel_position = (y * img->len) + (x * (img->bpp >> 3));
	pixel = img->addr + pixel_position;
	*(unsigned int *)pixel = color;
}



// /*
//  * will place the respective wall image to the mlx_window if the current tile
//  * on the 2d map is '1'
//  *
//  * i[0] = index for 2D array
//  * i[1] = index to read each element in array[i[0]]
//  */
// void	plot_map(t_data *data)
// {
// 	int	i[2];

// 	i[0] = -1;
// 	while(data->map[++i[0]])
// 	{
// 		i[1] = -1;
// 		while (data->map[i[0]][++i[1]])
// 		{
// 			if (data->map[i[0]][i[1]] == '1')
// 			{
// 				mlx_put_image_to_window(data->mlx, data->window, data->wall,
// 				i[1] * data->wall_width, i[0] * data->wall_height);
// 			}
// 		}
// 	}
// }

// /*
//  * searches for the first occurence of a 0 character from the 2d map and
//  * sets the player's starting position to that specific coordinate
//  */
// void	set_player_position(t_data *data)
// {
// 	int i[3];
		
// 	i[2] = 0;
// 	i[0] = -1;
// 	while (data->map[++i[0]])
// 	{
// 		i[1] = -1;
// 		while (data->map[i[0]][++i[1]])
// 		{
// 			if (data->map[i[0]][i[1]] == '0')
// 			{
// 				data->px = i[1] * data->wall_width;
// 				data->py = i[0] * data->wall_height;
// 				i[2] = 1;
// 				break ;
// 			}
// 		}
// 		if (i[2])
// 			break ;
// 	}
// }

// void	plot_player(t_data *data)
// {
// 	data->img[1].addr = mlx_get_data_addr(data->img[1].img, &data->img[1].bpp,
// 		&data->img[1].len, &data->img[1].endian);
// 	{
// 		float i = -1;
// 		while (++i < data->player_height)
// 		{
// 			float j = -1;
// 			while (++j < data->player_width)
// 			{
// 				// if (i >= data->player_height * 0.25 && i <= data->player_height * 0.75
// 				// 	&& j >= data->player_width * 0.25 && j <= data->player_width * 0.75)
// 					put_pixel_at_addr(&data->img[1], i, j, 0xFF0000);
// 			}
// 		}
// 	}
// 	data->player = data->img[1].img;
// 	mlx_put_image_to_window(data->mlx, data->window, data->player, data->px, data->py);
// }

// bool	is_quadrant_angle(double n)
// {
// 	if (n == 0 || n == 90 || n == 180 || n == 270 || n == 360)
// 		return (true);
// 	return (false);
// }

// void	print_player_angle(t_data *data)
// {
// 	char	*temp;
	
// 	temp = ft_itoa((int)data->pa);
// 	mlx_string_put(data->mlx, data->window, 25, 25, 0x00FFFF, temp);
// 	mlx_string_put(data->mlx, data->window, 47.5, 25, 0x00FFFF, "deg.");
// 	free(temp);
// 	temp = NULL;
// }

// int	keyboard_events(int input, t_data *data)
// {
// 	// printf("%d\n", input);	// print keycodes
// 	if (input == KEYCODE_ESC)
// 		close_window(data);
// 	else if (input == KEYCODE_W)
// 	{
// 		data->px += data->pdx;
// 		data->py -= data->pdy;
// 	}
// 	else if (input == KEYCODE_A)
// 	{
// 		if (is_quadrant_angle(data->pa))
// 		{
// 			if (!data->pa || data->pa == 360)
// 				data->py -= data->player_speed;
// 			else if (data->pa == 90)
// 				data->px -= data->player_speed;
// 			else if (data->pa == 180)
// 				data->py += data->player_speed;
// 			else if (data->pa == 270)
// 				data->px += data->player_speed;
// 		}
// 		else if ((data->pa > 0 && data->pa < 90) || (data->pa > 180 && data->pa < 270))
// 		{
// 			data->px -= data->pdx;
// 			data->py -= data->pdy;
// 		}
// 		else
// 		{
// 			data->px += data->pdx;
// 			data->py += data->pdy;
// 		}
// 	}
// 	else if (input == KEYCODE_S)
// 	{
// 		data->px -= data->pdx;
// 		data->py += data->pdy;
// 	}
// 	else if (input == KEYCODE_D)
// 	{
// 		if (is_quadrant_angle(data->pa))
// 		{
// 			if (!data->pa || data->pa == 360)
// 				data->py += data->player_speed;
// 			else if (data->pa == 90)
// 				data->px += data->player_speed;
// 			else if (data->pa == 180)
// 				data->py -= data->player_speed;
// 			else if (data->pa == 270)
// 				data->px -= data->player_speed;
// 		}
// 		else if ((data->pa > 0 && data->pa < 90) || (data->pa > 180 && data->pa < 270))
// 		{
// 			data->px += data->pdx;
// 			data->py += data->pdy;
// 		}
// 		else
// 		{
// 			data->px -= data->pdx;
// 			data->py -= data->pdy;
// 		}
// 	}
// 	// else if (input == KEYCODE_UP)
// 	// {
		
// 	// }
// 	// else if (input == KEYCODE_DOWN)
// 	// {

// 	// }
// 	else if (input == KEYCODE_LEFT)
// 	{
// 		data->pa -= 2.5;
// 		if (data->pa < 0)
// 			data->pa += 360;
// 		data->pdx = cos(data->pa * PI / 180) * data->player_speed;
// 		data->pdy = sin(data->pa * PI / 180) * data->player_speed;
// 	}
// 	else if (input == KEYCODE_RIGHT)
// 	{
// 		data->pa += 2.5;
// 		if (data->pa > 360)
// 			data->pa -= 360;
// 		data->pdx = cos(data->pa * PI / 180) * data->player_speed;
// 		data->pdy = sin(data->pa * PI / 180) * data->player_speed;
// 	}

// 	mlx_clear_window(data->mlx, data->window);
// 	plot_map(data);
// 	plot_player(data);
// 	print_player_angle(data);
	
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	t_data	data;
// 	int		map_lines;

// 	if (argc == 2)
// 	{
// 		// Parsing of Map
// 		check_map_extension(argv[1]);
// 		map_lines = check_map_validity(argv[1]);
// 		data.map = save_map(argv[1], map_lines);


// 		data.mlx = mlx_init();
// 		mlx_get_screen_size(data.mlx, &data.width, &data.height);
// 		data.window = mlx_new_window(data.mlx, data.width, data.height, "cub3D");


// 		// // Creating Wall Img
// 		// data.wall_width = WALL_WIDTH;
// 		// data.wall_height = WALL_HEIGHT;
// 		// data.img[0].img = mlx_new_image(data.mlx, data.wall_width, data.wall_height);
// 		// data.img[0].addr = mlx_get_data_addr(data.img[0].img, &data.img[0].bpp, &data.img[0].len, &data.img[0].endian);
// 		// {
// 		// 	int i = -1;
// 		// 	while (++i < data.wall_height)
// 		// 	{
// 		// 		int j = -1;
// 		// 		while (++j < data.wall_width)
// 		// 			put_pixel_at_addr(&data.img[0], i, j, 0xFFFFFF);
// 		// 	}
// 		// }
// 		// data.wall = data.img[0].img;


// 		// // Creating Player Img
// 		// data.pa = 0;
// 		// data.player_speed = 2.50;
// 		// data.pdx = cos(data.pa * PI / 180) * data.player_speed;
// 		// data.pdy = sin(data.pa * PI / 180) * data.player_speed;
// 		// data.player_width = data.wall_width / 2;
// 		// data.player_height = data.wall_height / 2;
// 		// data.img[1].img = mlx_new_image(data.mlx, data.player_width, data.player_height);


// 		// plot_map(&data);
// 		// set_player_position(&data);
// 		// plot_player(&data);
// 		// print_player_angle(&data);
		

// 		// mlx_hook(data.window, 2, 1L<<0, keyboard_events, &data);
// 		// mlx_hook(data.window, 17, 1L<<17, close_window, &data);
// 		// mlx_loop(data.mlx);



// 		return (0);
// 	}
// 	ft_putstr_fd("Invalid Arguments\n", 2);
// 	return (1);
// }


/*
 * draws a vertical line to our image's address according to the specified
 * starting and ending points. Used for untextured raycasting
 */
void	draw_line(t_img	*img, int x, int start, int end, int color)
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
void	draw_walls(t_data *data, int (*buffer)[data->win_width])
{
	int	i[2];
	
	i[0] = -1;
	while (++i[0] < data->win_height)
	{
		i[1] = -1;
		while (++i[1] < data->win_width)
			put_pixel_at_addr(&data->img[0], i[1], i[0], buffer[i[0]][i[1]]);
	}
}

int	raycast_loop(t_data *data)
{
	t_calculations calc;

	ft_bzero(calc, sizeof(t_calculations));
	

	
	int buffer[data->win_height][data->win_width];
	for (int i = 0; i < data->win_height; i++) {
		for (int j = 0; j < data->win_width; j++) {
			buffer[i][j] = 0;
		}
	}

	for (int x = 0; x < data->win_width; x++) {
		
		double	camera_x = 2 * x / (double)data->win_width - 1;
		double	ray_dir_x = data->vec_x + data->plane_x * camera_x;
		double	ray_dir_y = data->vec_y + data->plane_y * camera_x;
		
		int	map_x = (int)data->pos_x;
		int	map_y = (int)data->pos_y;

		double	side_dist_x = 0;
		double	side_dist_y = 0;

		double	delta_dist_x = fabs(1 / ray_dir_x);
		double	delta_dist_y = fabs(1 / ray_dir_y);
		double	perp_dist = 0;

		int	step_x = 0;
		int	step_y = 0;
		// int hit = 0;
		int side = 0;
		
		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (data->pos_x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->pos_x) * delta_dist_x;
		}

		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (data->pos_y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->pos_y) * delta_dist_y;
		}


		// DDA Algorithm
		while (1) {
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map[map_y][map_x] == '1')
				break ;
		}


		if (!side)
			perp_dist = side_dist_x - delta_dist_x;
		else
			perp_dist = side_dist_y - delta_dist_y;


		int	line_height = (int)(data->win_height / perp_dist);
		int	draw_start = -line_height / 2 + data->win_height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int	draw_end = line_height / 2 + data->win_height / 2;
		if (draw_end >= data->win_height)
			draw_end = data->win_height - 1;


		double wall_x;
		if (!side)
			wall_x = data->pos_y + perp_dist * ray_dir_y;
		else
			wall_x = data->pos_x + perp_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		int	texture_x = (int)(wall_x * (double)data->texture_width);
		if (!side && ray_dir_x > 0)
			texture_x = data->texture_width - texture_x - 1;
		else if (side && ray_dir_y < 0)
			texture_x = data->texture_width - texture_x - 1;

		double step = 1.0 * data->texture_height / line_height;
		double texture_pos = (draw_start - data->win_height / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			int	texture_y = (int)texture_pos & (data->texture_height - 1);
			texture_pos += step;
			int	color = data->img[1].pixel[data->texture_height * texture_y + texture_x];
			if (side)
				color = (color >> 1) & 8355711;
			buffer[y][x] = color;
		}


		// int	color = 0xFFFFFF;
		// if (data->map[map_y][map_x] == '1')
		// 	color = 0xAA0000;
		// if (side)
		// 	color /= 2;
		// draw_line(&data->img[0], x, draw_start, draw_end, color);
	}
	draw_walls(data, buffer);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img[0].ptr, 0, 0);
	return (0);
}

int	close_window(t_data *data)
{
	free_2d_array(data->map);
	mlx_destroy_image(data->mlx, data->img[0].ptr);
	mlx_destroy_image(data->mlx, data->img[1].ptr);
	mlx_clear_window(data->mlx, data->mlx_window);
	mlx_destroy_window(data->mlx, data->mlx_window);
	exit(0);
}

int	key_events(int input, t_data *data)
{
	if (input == KEYCODE_ESC)
		close_window(data);
	else if (input == KEYCODE_W)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x + data->vec_x * data->move_speed)] == '0')
			data->pos_x += data->vec_x * data->move_speed;
		if (data->map[(int)(data->pos_y + data->vec_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y += data->vec_y * data->move_speed;
	}
	else if (input == KEYCODE_A)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x - data->plane_x * data->move_speed)] == '0')
			data->pos_x -= data->plane_x * data->move_speed;
		if (data->map[(int)(data->pos_y - data->plane_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y -= data->plane_y * data->move_speed;
	}
	else if (input == KEYCODE_S)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x - data->vec_x * data->move_speed)] == '0')
			data->pos_x -= data->vec_x * data->move_speed;
		if (data->map[(int)(data->pos_y - data->vec_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y -= data->vec_y * data->move_speed;
	}
	else if (input == KEYCODE_D)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x + data->plane_x * data->move_speed)] == '0')
			data->pos_x += data->plane_x * data->move_speed;
		if (data->map[(int)(data->pos_y + data->plane_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y += data->plane_y * data->move_speed;
	}
	else if (input == KEYCODE_LEFT)
	{
		double	old_vec_x = data->vec_x;
		data->vec_x = data->vec_x * cos(-data->rotate_speed) - data->vec_y * sin(-data->rotate_speed);
		data->vec_y = old_vec_x * sin(-data->rotate_speed) + data->vec_y * cos(-data->rotate_speed);
		double	old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-data->rotate_speed) - data->plane_y * sin(-data->rotate_speed);
		data->plane_y = old_plane_x * sin(-data->rotate_speed) + data->plane_y * cos(-data->rotate_speed);
	}
	else if (input == KEYCODE_RIGHT)
	{
		double	old_vec_x = data->vec_x;
		data->vec_x = data->vec_x * cos(data->rotate_speed) - data->vec_y * sin(data->rotate_speed);
		data->vec_y = old_vec_x * sin(data->rotate_speed) + data->vec_y * cos(data->rotate_speed);
		double	old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(data->rotate_speed) - data->plane_y * sin(data->rotate_speed);
		data->plane_y = old_plane_x * sin(data->rotate_speed) + data->plane_y * cos(data->rotate_speed);
	}
	
	mlx_destroy_image(data->mlx, data->img[0].ptr);
	data->img[0].ptr = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img[0].addr = mlx_get_data_addr(data->img[0].ptr, &data->img[0].bpp, &data->img[0].len, &data->img[0].endian);
	mlx_clear_window(data->mlx, data->mlx_window);
	raycast_loop(data);
	
	return (0);
}

/*
 * parses the map and sets the player's starting location at the first 
 * occurence of a '0' character
 * 
 * i[0] = index for y-axis of map
 * i[1] = index for x-axis of map
 * i[2] = acts like a boolean to indicate if the player's starting
 *        location has been set
 */
void	set_player_position(t_data *data)
{
	int	i[3];

	i[2] = 0;
	i[0] = -1;
	while (data->map[++i[0]])
	{
		i[1] = -1;
		while (data->map[i[0]][++i[1]])
		{
			if (data->map[i[0]][i[1]] == '0')
			{
				data->pos_x = i[1] + 0.50;
				data->pos_y = i[0] + 0.50;
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
	t_data	data;

	if (argc == 2) {
		check_map_extension(argv[1]);
		data.map = save_map(argv[1], check_map_validity(argv[1]));

		data.mlx = mlx_init();
		mlx_get_screen_size(data.mlx, &data.win_width, &data.win_height);
		data.win_width /= 1.65;
		data.win_height /= 1.35;
		data.mlx_window = mlx_new_window(data.mlx, data.win_width, data.win_height, "cub3D");

		data.img[0].ptr = mlx_new_image(data.mlx, data.win_width, data.win_height);
		data.img[0].addr = mlx_get_data_addr(data.img[0].ptr, &data.img[0].bpp, &data.img[0].len, &data.img[0].endian);
		data.img[1].ptr = mlx_xpm_file_to_image(data.mlx, "assets/multibrick.xpm", &data.texture_width, &data.texture_height);
		data.img[1].pixel = (int *)mlx_get_data_addr(data.img[1].ptr, &data.img[1].bpp, &data.img[1].len, &data.img[1].endian);

		set_player_position(&data);
		data.vec_x = 1;
		data.vec_y = 0;
		data.plane_x = 0;
		data.plane_y = 0.66;
		data.move_speed = 0.065;
		data.rotate_speed = 0.035;

		raycast_loop(&data);
		mlx_hook(data.mlx_window, 2, 1L<<0, key_events, &data);
		mlx_loop(data.mlx);
		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}