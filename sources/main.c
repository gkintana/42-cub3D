/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/08 01:02:42 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
 * this function simply checks if the argument being passed is a file with a
 * .cub extension.
 *
 * Note: will still work or sometimes even segfault when given
 *      ./cub3d maps/minimalist_map_only.cub.cub
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
  saves the map in a 2d array if it passes the parser
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
	while (i < lines)
	{
		map[i] = ft_strdup(temp);
		free(temp);
		temp = get_next_line(fd);
		i++;
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

// int	close_window(t_data *data)
// {
// 	free_2d_array(data->map);
// 	mlx_destroy_image(data->mlx, data->wall);
// 	mlx_destroy_image(data->mlx, data->player);
// 	mlx_clear_window(data->mlx, data->window);
// 	mlx_destroy_window(data->mlx, data->window);
// 	exit(0);
// }

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

void	draw_line(t_data *data, int x, int start, int end, int color)
{
	int	i;

	i = start;
	while (i <= end)
	{
		mlx_pixel_put(data->mlx, data->mlx_window, x, i, color);
		// put_pixel_at_addr(&data->img, x, i, color);
		i++;
	}
	// data->render = data->img.ptr;
}

// untextured version - part I of Lode's Raycasting Tutorial
int	raycast_loop(t_data *data)
{
	for (int x = 0; x < data->win_width; x++) {
		
		double	camera_x = 2 * x / (double)data->win_width - 1;
		double	ray_dir_x = data->vector_x + data->plane_x * camera_x;
		double	ray_dir_y = data->vector_y + data->plane_y * camera_x;
		
		int	map_x = (int)data->position_x;
		int	map_y = (int)data->position_y;

		double	side_dist_x = 0;
		double	side_dist_y = 0;

		double	delta_dist_x = !ray_dir_x ? 1e30 : fabs(1 / ray_dir_x);
		double	delta_dist_y = !ray_dir_y ? 1e30 : fabs(1 / ray_dir_y);
		double	perp_dist = 0;

		int	step_x = 0;
		int	step_y = 0;
		// int hit = 0;
		int side = 0;
		
		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (data->position_x - map_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->position_x) * delta_dist_x;
		}

		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (data->position_y - map_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->position_y) * delta_dist_y;
		}


		// DDA Algorithm
		// while (!hit) {
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
			// printf("map_x = %d\nmap_y = %d\n", map_x, map_y);
			if (data->map[map_y][map_x] == '1')
				break ;
				// hit = 1;
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

		int	color = 0xFFFFFF;
		// switch(ft_atoi(data->map[map_y][map_x])) {
		// 	case 1:
		// 		color = 0xFF0000;
		// 		break;
		// 	case 2:
		// 		color = 0x00FF00;
		// 		break;
		// 	case 3:
		// 		color = 0x0000FF;
		// 		break;
		// 	case 4:
		// 		color = 0xFFFFFF;
		// 		break;
		// 	default:
		// 		color = 0xFFFF00;
		// 		break;
		// }
		if (data->map[map_y][map_x] == '1')
			color = 0x0000FF;
		// else
		// 	color = 

		if (side)
			color /= 2;

		draw_line(data, x, draw_start, draw_end, color);
		// mlx_put_image_to_window(data->mlx, data->mlx_window, data->render, 0, 0);
		
		// skipped input timer, fps counter and speed modifiers
		
	}
	return (0);
}

int	close_window(t_data *data)
{
	free_2d_array(data->map);
	mlx_clear_window(data->mlx, data->mlx_window);
	mlx_destroy_window(data->mlx, data->mlx_window);
	exit(0);
}

int	keyboard_events(int input, t_data *data)
{
	if (input == KEYCODE_ESC)
		close_window(data);
	else if (input == KEYCODE_W)
	{
		if (data->map[(int)data->position_y][(int)(data->position_x + data->vector_x * MOVE)] == '0')
			data->position_x += data->vector_x * MOVE;
		if (data->map[(int)(data->position_y + data->vector_y * MOVE)][(int)data->position_x] == '0')
			data->position_y += data->vector_y * MOVE;
	}
	else if (input == KEYCODE_S)
	{
		if (data->map[(int)data->position_y][(int)(data->position_x - data->vector_x * MOVE)] == '0')
			data->position_x -= data->vector_x * MOVE;
		if (data->map[(int)(data->position_y - data->vector_y * MOVE)][(int)data->position_x] == '0')
			data->position_y -= data->vector_y * MOVE;
	}
	else if (input == KEYCODE_LEFT)
	{
		double	old_vector_x = data->vector_x;
		data->vector_x = data->vector_x * cos(-ROT) - data->vector_y * sin(-ROT);
		data->vector_y = old_vector_x * sin(-ROT) + data->vector_y * cos(-ROT);
		double	old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-ROT) - data->plane_y * sin(-ROT);
		data->plane_y = old_plane_x * sin(-ROT) + data->plane_y * cos(-ROT);
	}
	else if (input == KEYCODE_RIGHT)
	{
		double	old_vector_x = data->vector_x;
		data->vector_x = data->vector_x * cos(ROT) - data->vector_y * sin(ROT);
		data->vector_y = old_vector_x * sin(ROT) + data->vector_y * cos(ROT);
		double	old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(ROT) - data->plane_y * sin(ROT);
		data->plane_y = old_plane_x * sin(ROT) + data->plane_y * cos(ROT);
	}
	
	mlx_clear_window(data->mlx, data->mlx_window);
	// raycast_loop(data);
	// mlx_put_image_to_window(data->mlx, data->mlx_window, data->render, 0, 0);
	
	return (0);
}

void	set_player_position(t_data *data)
{
	int i[3];
		
	i[2] = 0;
	i[0] = -1;
	while (data->map[++i[0]])
	{
		i[1] = -1;
		while (data->map[i[0]][++i[1]])
		{
			if (data->map[i[0]][i[1]] == '0')
			{
				data->position_x = i[1] + 0.50;
				data->position_y = i[0] + 0.50;
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
	int		map_lines;

	if (argc == 2) {
		check_map_extension(argv[1]);
		map_lines = check_map_validity(argv[1]);
		data.map = save_map(argv[1], map_lines);

		data.mlx = mlx_init();
		mlx_get_screen_size(data.mlx, &data.win_width, &data.win_height);
		data.win_width /= 2.500;
		data.win_height /= 2.000;
		data.mlx_window = mlx_new_window(data.mlx, data.win_width, data.win_height, "cub3D");
		data.img.ptr = mlx_new_image(data.mlx, data.win_width, data.win_height);
		data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.len, &data.img.endian);

		set_player_position(&data);
		data.vector_x = 1;
		data.vector_y = 0;
		data.plane_x = 0;
		data.plane_y = 0.66;
		// data.time_new = 0;
		// data.time_old = 0;
		// raycast_loop(&data);
		mlx_loop_hook(data.mlx, raycast_loop, &data);
		mlx_hook(data.mlx_window, 2, 1L<<0, keyboard_events, &data);
		// mlx_hook(data.mlx_window, 17, 1L<<17, close_window, &data);
		mlx_loop(data.mlx);
		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}