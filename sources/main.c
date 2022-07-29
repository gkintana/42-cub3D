/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 01:01:52 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/29 12:12:54 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

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
		prog.mlx.img[1].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.north, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[1].pixel = (int *)mlx_get_data_addr(prog.mlx.img[1].ptr, &prog.mlx.img[1].bpp, &prog.mlx.img[1].len, &prog.mlx.img[1].endian);
		prog.mlx.img[2].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.south, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[2].pixel = (int *)mlx_get_data_addr(prog.mlx.img[2].ptr, &prog.mlx.img[2].bpp, &prog.mlx.img[2].len, &prog.mlx.img[2].endian);
		prog.mlx.img[3].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.east, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[3].pixel = (int *)mlx_get_data_addr(prog.mlx.img[3].ptr, &prog.mlx.img[3].bpp, &prog.mlx.img[3].len, &prog.mlx.img[2].endian);
		prog.mlx.img[4].ptr = mlx_xpm_file_to_image(prog.mlx.ptr, prog.tex.west, &prog.tex.width, &prog.tex.height);
		prog.mlx.img[4].pixel = (int *)mlx_get_data_addr(prog.mlx.img[4].ptr, &prog.mlx.img[4].bpp, &prog.mlx.img[4].len, &prog.mlx.img[4].endian);

		set_player_position(&prog);
		set_player_orientation(&prog);
		
		// NORTH
		// prog.info.vec_x = 0;
		// prog.info.vec_y = -1;
		// prog.info.plane_x = 0.66;
		// prog.info.plane_y = 0;

		// SOUTH 
		// prog.info.vec_x = 0;
		// prog.info.vec_y = 1;
		// prog.info.plane_x = -0.66;
		// prog.info.plane_y = 0;

		// EAST
		// prog.info.vec_x = 1;
		// prog.info.vec_y = 0;
		// prog.info.plane_x = 0;
		// prog.info.plane_y = 0.66;

		// WEST
		// prog.info.vec_x = -1;
		// prog.info.vec_y = 0;
		// prog.info.plane_x = 0;
		// prog.info.plane_y = -0.66;
		
		prog.info.pitch = 0;
		prog.info.move_speed = 0.085;
		prog.info.rotate_speed = 0.045;

		prog.map.scale = 100;
		prog.map.offset_x = 15;
		prog.map.offset_y = 15;

		raycast_loop(&prog);
		mlx_hook(prog.mlx.window, 2, 1L<<0, key_events, &prog);
		mlx_hook(prog.mlx.window, 6, 1L<<6, mouse_events, &prog);
		mlx_hook(prog.mlx.window, 17, 1L<<17, close_window, &prog);
		mlx_loop(prog.mlx.ptr);
		return (0);
	}
	ft_putstr_fd("Invalid Arguments\n", 2);
	return (1);
}
