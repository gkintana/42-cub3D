/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/08/01 17:11:07 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D_bonus.h>

void	intro(t_program *prog)
{
	int		width[3];
	int		height[3];
	void	*pic[3];

	ft_bzero(pic, sizeof(void *) * 3);
	pic[0] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/1.xpm",
		&width[0], &height[0]);
	pic[1] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/2.xpm",
		&width[1], &height[1]);
	pic[2] = mlx_xpm_file_to_image(prog->mlx.ptr, "assets/intro/4.xpm",
		&width[2], &height[2]);
	int	i = 0;
	while (i < 3)
	{
		mlx_put_image_to_window(prog->mlx.ptr, prog->mlx.window, pic[i], 0, 0);
		sleep(2);
		mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
		mlx_destroy_image(prog->mlx.ptr, pic[i]);
		pic[i] = NULL;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_program	prog;

	if (argc == 2)
	{
		ft_bzero(&prog, sizeof(t_program));
		check_map_validity(argv[1]);
		check_map_extension(argv[1]);
		if (!check_elements(argv[1], &prog))
		{
			intro(&prog);
			get_floor_and_ceiling_rgb(&prog);
			raycast_loop(&prog);
			mlx_mouse_hide(prog.mlx.ptr, prog.mlx.window);
			mlx_hook(prog.mlx.window, 6, 1L << 6, mouse_events, &prog);
			mlx_hook(prog.mlx.window, 2, 1L << 0, key_events, &prog);
			mlx_hook(prog.mlx.window, 17, 1L << 17, close_window, &prog);
			mlx_loop(prog.mlx.ptr);
			return (0);
		}
	}
	ft_putstr_fd("Error\nInvalid Arguments\n", 2);
	return (1);
}
