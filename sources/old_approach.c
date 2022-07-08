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