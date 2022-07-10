/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:54:46 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/10 21:13:18 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	key_events(int input, t_program *prog)
{
	if (input == KEYCODE_ESC)
		close_window(prog);
	else if (input == KEYCODE_W)
	{
		if (prog->mlx.map[(int)prog->info.pos_y][(int)(prog->info.pos_x + prog->info.vec_x * prog->info.move_speed)] == '0')
			prog->info.pos_x += prog->info.vec_x * prog->info.move_speed;
		if (prog->mlx.map[(int)(prog->info.pos_y + prog->info.vec_y * prog->info.move_speed)][(int)prog->info.pos_x] == '0')
			prog->info.pos_y += prog->info.vec_y * prog->info.move_speed;
	}
	else if (input == KEYCODE_A)
	{
		if (prog->mlx.map[(int)prog->info.pos_y][(int)(prog->info.pos_x - prog->info.plane_x * prog->info.move_speed)] == '0')
			prog->info.pos_x -= prog->info.plane_x * prog->info.move_speed;
		if (prog->mlx.map[(int)(prog->info.pos_y - prog->info.plane_y * prog->info.move_speed)][(int)prog->info.pos_x] == '0')
			prog->info.pos_y -= prog->info.plane_y * prog->info.move_speed;
	}
	else if (input == KEYCODE_S)
	{
		if (prog->mlx.map[(int)prog->info.pos_y][(int)(prog->info.pos_x - prog->info.vec_x * prog->info.move_speed)] == '0')
			prog->info.pos_x -= prog->info.vec_x * prog->info.move_speed;
		if (prog->mlx.map[(int)(prog->info.pos_y - prog->info.vec_y * prog->info.move_speed)][(int)prog->info.pos_x] == '0')
			prog->info.pos_y -= prog->info.vec_y * prog->info.move_speed;
	}
	else if (input == KEYCODE_D)
	{
		if (prog->mlx.map[(int)prog->info.pos_y][(int)(prog->info.pos_x + prog->info.plane_x * prog->info.move_speed)] == '0')
			prog->info.pos_x += prog->info.plane_x * prog->info.move_speed;
		if (prog->mlx.map[(int)(prog->info.pos_y + prog->info.plane_y * prog->info.move_speed)][(int)prog->info.pos_x] == '0')
			prog->info.pos_y += prog->info.plane_y * prog->info.move_speed;
	}
	else if (input == KEYCODE_LEFT)
	{
		double	old_vec_x = prog->info.vec_x;
		prog->info.vec_x = prog->info.vec_x * cos(-prog->info.rotate_speed) - prog->info.vec_y * sin(-prog->info.rotate_speed);
		prog->info.vec_y = old_vec_x * sin(-prog->info.rotate_speed) + prog->info.vec_y * cos(-prog->info.rotate_speed);
		double	old_plane_x = prog->info.plane_x;
		prog->info.plane_x = prog->info.plane_x * cos(-prog->info.rotate_speed) - prog->info.plane_y * sin(-prog->info.rotate_speed);
		prog->info.plane_y = old_plane_x * sin(-prog->info.rotate_speed) + prog->info.plane_y * cos(-prog->info.rotate_speed);
	}
	else if (input == KEYCODE_RIGHT)
	{
		double	old_vec_x = prog->info.vec_x;
		prog->info.vec_x = prog->info.vec_x * cos(prog->info.rotate_speed) - prog->info.vec_y * sin(prog->info.rotate_speed);
		prog->info.vec_y = old_vec_x * sin(prog->info.rotate_speed) + prog->info.vec_y * cos(prog->info.rotate_speed);
		double	old_plane_x = prog->info.plane_x;
		prog->info.plane_x = prog->info.plane_x * cos(prog->info.rotate_speed) - prog->info.plane_y * sin(prog->info.rotate_speed);
		prog->info.plane_y = old_plane_x * sin(prog->info.rotate_speed) + prog->info.plane_y * cos(prog->info.rotate_speed);
	}
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[0].ptr);
	prog->mlx.img[0].ptr = mlx_new_image(prog->mlx.ptr, prog->mlx.win_width, prog->mlx.win_height);
	prog->mlx.img[0].addr = mlx_get_data_addr(prog->mlx.img[0].ptr, &prog->mlx.img[0].bpp, &prog->mlx.img[0].len, &prog->mlx.img[0].endian);
	// mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[1].ptr);
	// // prog.tex.north is temporary
	// prog->mlx.img[1].ptr = mlx_xpm_file_to_image(prog->mlx.ptr, prog->tex.north, &prog->tex.width, &prog->tex.height);
	// prog->mlx.img[1].pixel = (int *)mlx_get_data_addr(prog->mlx.img[1].ptr, &prog->mlx.img[1].bpp, &prog->mlx.img[1].len, &prog->mlx.img[1].endian);
	mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
	raycast_loop(prog);
	return (0);
}