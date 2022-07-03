/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/03 22:31:55 by gkintana         ###   ########.fr       */
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

int	close_window(t_img *img)
{
	mlx_clear_window(img->mlx, img->window);
	mlx_destroy_window(img->mlx, img->window);
	free_2d_array(img->map);
	exit(0);
}

/*
 * i[0] = index for 2D array
 * i[1] = index to read each element in array[i[0]]
 */
void	plot_map(t_img *img)
{
	int	i[2];

	i[0] = -1;
	while(img->map[++i[0]])
	{
		i[1] = -1;
		while (img->map[i[0]][++i[1]])
		{
			if (img->map[i[0]][i[1]] == '1')
			{
				mlx_put_image_to_window(img->mlx, img->window, img->wall,
				i[1] * img->wall_width, i[0] * img->wall_height);
			}
		}
	}
}

int	keyboard_events(int key_code, t_img *img)
{
	if (key_code == 65307)
		close_window(img);
	else if (key_code == 97)
	{
		if (img->map[img->y / img->wall_height][(img->x / img->wall_width) - 1] == '0')
			img->x -= img->wall_width;
	}
	else if (key_code == 100)
	{
		if (img->map[img->y / img->wall_height][(img->x / img->wall_width) + 1] == '0')
			img->x += img->wall_width;
	}
	else if (key_code == 119)
	{
		if (img->map[(img->y / img->wall_height) - 1][img->x / img->wall_width] == '0')
			img->y -= img->wall_height;
	}
	else if (key_code == 115)
	{
		if (img->map[(img->y / img->wall_height) + 1][img->x / img->wall_width] == '0')
			img->y += img->wall_height;
	}

	// mlx_destroy_image(img->mlx, img->player);
	mlx_clear_window(img->mlx, img->window);
	plot_map(img);
	mlx_put_image_to_window(img->mlx, img->window, img->player, img->x, img->y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_img	img;
	int		map_lines;

	if (argc == 2)
	{
		check_map_extension(argv[1]);
		map_lines = check_map_validity(argv[1]);
		img.map = save_map(argv[1], map_lines);

		img.mlx = mlx_init();
		img.window = mlx_new_window(img.mlx, 1000, 800, "cub3D Test");

		img.white = "xpm/white.xpm";
		img.wall = mlx_xpm_file_to_image(img.mlx, img.white, &img.wall_width, &img.wall_height);
		img.yellow = "xpm/yellow.xpm";
		img.player = mlx_xpm_file_to_image(img.mlx, img.yellow, &img.player_width, &img.player_height);
		
		plot_map(&img);

		img.x = 2 * img.player_width;
		img.y = 2 * img.player_height;
		mlx_put_image_to_window(img.mlx, img.window, img.player, img.x, img.y);


		// mlx_do_key_autorepeaton(img.mlx);
		mlx_key_hook(img.window, keyboard_events, &img);
		mlx_hook(img.window, 17, 1L<<17, close_window, &img);
		mlx_loop(img.mlx);

		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}
