/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/03 19:09:47 by gkintana         ###   ########.fr       */
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

void	check_map_validity(char *file)
{
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
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
	}
	free(str);
}

int	close_window(t_img *img)
{
	mlx_clear_window(img->mlx, img->window);
	mlx_destroy_window(img->mlx, img->window);
	exit(0);
}

int	keyboard_events(int key_code, t_img *img)
{
	if (key_code == 65307)
		close_window(img);
	else if (key_code == 97)
		img->x -= 42;
	else if (key_code == 100)
		img->x += 42;
	else if (key_code == 119)
		img->y -= 42;
	else if (key_code == 115)
		img->y += 42;

	// mlx_clear_window(img->mlx, img->window);
	// mlx_destroy_image(img->mlx, img->player);
	mlx_put_image_to_window(img->mlx, img->window, img->player, img->x, img->y);
	
	return (0);
}

void	draw_test(char *file, t_img *img)
{
	char	*str;
	int		fd;
	int		i;
	int		j;

	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while(str)
	{
		printf("%s", str);
		j = 0;
		while (str[j])
		{
			if (str[j] == '1')
			{
				mlx_put_image_to_window(img->mlx, img->window, img->wall, 
					(j * img->wall_width) + img->x, (i * img->wall_height) + img->y);
			}
			j++;
		}
		free(str);
		str = get_next_line(fd);
		i++;
	}
}

int	main(int argc, char **argv)
{
	// void	*mlx;
	// void	*mlx_win;
	t_img	img;

	if (argc == 2)
	{
		check_map_extension(argv[1]);
		check_map_validity(argv[1]);

		img.mlx = mlx_init();
		img.window = mlx_new_window(img.mlx, 1000, 800, "cub3D Test");

		
		
		img.white = "xpm/white.xpm";
		img.yellow = "xpm/yellow.xpm";
		
		img.wall = mlx_xpm_file_to_image(img.mlx, img.white, &img.wall_width, &img.wall_height);
		img.player = mlx_xpm_file_to_image(img.mlx, img.yellow, &img.player_width, &img.player_height);
		// mlx_put_image_to_window(mlx, mlx_win, img.ptr, 0, 0);
		
		draw_test(argv[1], &img);

		img.x = 2 * img.player_width;
		img.y = 2 * img.player_height;
		mlx_put_image_to_window(img.mlx, img.window, img.player, img.x, img.y);
		// mlx_put_image_to_window(img.mlx, img.window, img.wall, img.x, img.y);


		// img.ptr = mlx_xpm_file_to_image(img.mlx, img.white, &img.width, &img.height);
		

		mlx_do_key_autorepeaton(img.mlx);
		mlx_key_hook(img.window, keyboard_events, &img);
		mlx_hook(img.window, 17, 1L<<17, close_window, &img);
		mlx_loop(img.mlx);

		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}
