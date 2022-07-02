/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/02 23:59:54 by gkintana         ###   ########.fr       */
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
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
}

int	close_window(void)
{
	exit(0);
}

void	put_pixel_at_addr(t_pixel *img, int x, int y, unsigned int color)
{
	char			*pixel;
	unsigned int	pixel_position;

	pixel_position = (y * img->line_len) + (x * (img->bits_per_pixel >> 3));
	pixel = img->address + pixel_position;
	*(unsigned int *)pixel = color;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_pixel	pixel;

	if (argc == 2)
	{
		check_map_extension(argv[1]);
		check_map_validity(argv[1]);

		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, 500, 500, "cub3D Test");


		pixel.img = mlx_new_image(mlx, 100, 100);
		pixel.address = mlx_get_data_addr(pixel.img, &pixel.bits_per_pixel,
			&pixel.line_len, &pixel.endian);
		put_pixel_at_addr(&pixel, 20, 20, 0xFFFFFF);
		mlx_put_image_to_window(mlx, mlx_win, pixel.img, 20, 20);


		mlx_hook(mlx_win, 17, 1L<<17, close_window, NULL);
		mlx_loop(mlx);

		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}
