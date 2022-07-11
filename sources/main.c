/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/10 21:32:48 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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

		prog.tex.north = "assets/xpm/wall_1.xpm";
		prog.tex.south = "assets/xpm/wall_2.xpm";
		prog.tex.east = "assets/xpm/wall_5.xpm";
		prog.tex.west = "assets/xpm/wall_4.xpm";

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
		prog.mlx.img[2].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.south, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[2].pixel = (int *)mlx_get_data_addr(prog.mlx.img[2].ptr, &prog.mlx.img[2].bpp, &prog.mlx.img[2].len, &prog.mlx.img[2].endian);
		prog.mlx.img[3].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.east, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[3].pixel = (int *)mlx_get_data_addr(prog.mlx.img[3].ptr, &prog.mlx.img[3].bpp, &prog.mlx.img[3].len, &prog.mlx.img[2].endian);
		prog.mlx.img[4].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.west, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[4].pixel = (int *)mlx_get_data_addr(prog.mlx.img[4].ptr, &prog.mlx.img[4].bpp, &prog.mlx.img[4].len, &prog.mlx.img[4].endian);

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