/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/02 23:04:16 by gkintana         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;

	if (argc == 2)
	{
		check_map_extension(argv[1]);
		check_map_validity(argv[1]);
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, 420, 420, "cub3D Test");

		mlx_hook(mlx_win, 17, 1L<<17, close_window, NULL);
		mlx_loop(mlx);
	}
	return (0);
}
