/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/06 01:29:46 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

int	check_map_validity(char *file)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
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

int	close_window(t_data *data)
{
	free_2d_array(data->map);
	mlx_clear_window(data->mlx, data->window);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

/*
 * i[0] = index for 2D array
 * i[1] = index to read each element in array[i[0]]
 */
void	plot_map(t_data *data)
{

	int	i[2];

	i[0] = -1;
	while(data->map[++i[0]])
	{
		i[1] = -1;
		while (data->map[i[0]][++i[1]])
		{
			if (data->map[i[0]][i[1]] == '1')
			{
				mlx_put_image_to_window(data->mlx, data->window, data->wall,
				i[1] * data->wall_width, i[0] * data->wall_height);
			}
		}
	}
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
				data->px = i[1] * data->player_width * 2;
				data->py = i[0] * data->player_height * 2;
				i[2] = 1;
				break ;
			}
		}
		if (i[2])
			break ;
	}
}

int	keyboard_events(int input, t_data *data)
{
	// printf("%d\n", input);	// print keycodes
	if (input == KEYCODE_ESC)
		close_window(data);
	else if (input == KEYCODE_W)
	{
		// if (data->map[(data->y / data->wall_height) - 1][data->x / data->wall_width] == '0')
			// data->y -= data->player_height / 4;
		data->px -= data->pdx;
		data->py -= data->pdy;
		
	}
	else if (input == KEYCODE_A)
	{
		// if (data->map[data->y / data->wall_height][(data->x / data->wall_width) - 1] == '0')
			// data->x -= data->player_width / 4;
		
		data->px -= data->pdx;
		data->py += data->pdy;
	}
	else if (input == KEYCODE_S)
	{
		// if (data->map[(data->y / data->wall_height) + 1][data->x / data->wall_width] == '0')
			// data->y += data->player_height / 4;
		data->px += data->pdx;
		data->py += data->pdy;
	}
	else if (input == KEYCODE_D)
	{
		// if (data->map[data->y / data->wall_height][(data->x / data->wall_width) + 1] == '0')
			// data->x += data->player_width / 4;
		
		data->px += data->pdx;
		data->py -= data->pdy;
	}
	else if (input == KEYCODE_UP)
	{
		
	}
	else if (input == KEYCODE_DOWN)
	{

	}
	else if (input == KEYCODE_LEFT)
	{
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * 3.1416;
		data->pdx = cos(data->pa) * 2.25;
		data->pdy = sin(data->pa) * 2.25;
	}
	else if (input == KEYCODE_RIGHT)
	{
		data->pa += 0.1;
		if (data->pa > 2 * 3.1416)
			data->pa += 2 * 3.1416;
		data->pdx = cos(data->pa) * 2.25;
		data->pdy = sin(data->pa) * 2.25;
	}

	mlx_clear_window(data->mlx, data->window);
	plot_map(data);
	mlx_put_image_to_window(data->mlx, data->window, data->player, data->px, data->py);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		map_lines;

	if (argc == 2)
	{
		check_map_extension(argv[1]);
		map_lines = check_map_validity(argv[1]);
		data.map = save_map(argv[1], map_lines);

		data.mlx = mlx_init();
		data.width = 1900;
		data.height = 800;
		data.window = mlx_new_window(data.mlx, data.width, data.height, "cub3D");

		data.white = "xpm/white.xpm";
		data.wall = mlx_xpm_file_to_image(data.mlx, data.white, &data.wall_width, &data.wall_height);
		data.yellow = "xpm/yellow.xpm";
		data.player = mlx_xpm_file_to_image(data.mlx, data.yellow, &data.player_width, &data.player_height);

		// data.img = mlx_new_image(data.mlx, 25, 25);
		// data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.len, &data.endian);
		// int i = 0;
		// while (i < 5)
		// 	my_mlx_pixel_put(&data, i, i, 0xFFFFFF);
		// data.player = data.img;
		


		data.pa = 60;
		data.pdx = cos(data.pa) * 2.25;
		data.pdy = sin(data.pa) * 2.25;

		set_player_position(&data);
		plot_map(&data);
		mlx_put_image_to_window(data.mlx, data.window, data.player, data.px, data.py);
		

		mlx_hook(data.window, 2, 1L<<0, keyboard_events, &data);
		mlx_hook(data.window, 17, 1L<<17, close_window, &data);
		mlx_loop(data.mlx);

		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}
