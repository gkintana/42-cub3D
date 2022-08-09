/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:54:46 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/29 12:00:39 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	vertical_movement(t_program *prog, bool move_forward)
{
	int	i[2];

	ft_bzero(&i, 2 * sizeof(int));
	if (move_forward)
	{
		i[0] = (int)(calculate_position_and_vector(prog, 1));
		i[1] = (int)(calculate_position_and_vector(prog, 2));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x += prog->info.vec_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y += prog->info.vec_y * prog->info.move_speed;
	}
	else
	{
		i[0] = (int)(calculate_position_and_vector(prog, 3));
		i[1] = (int)(calculate_position_and_vector(prog, 4));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x -= prog->info.vec_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y -= prog->info.vec_y * prog->info.move_speed;
	}
}

static void	horizontal_movement(t_program *prog, bool move_left)
{
	int	i[2];

	ft_bzero(&i, 2 * sizeof(int));
	if (move_left)
	{
		i[0] = (int)(calculate_position_and_plane(prog, 1));
		i[1] = (int)(calculate_position_and_plane(prog, 2));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x -= prog->info.plane_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y -= prog->info.plane_y * prog->info.move_speed;
	}
	else
	{
		i[0] = (int)(calculate_position_and_plane(prog, 3));
		i[1] = (int)(calculate_position_and_plane(prog, 4));
		if (prog->mlx.map[(int)prog->info.pos_y][i[0]] != '1')
			prog->info.pos_x += prog->info.plane_x * prog->info.move_speed;
		if (prog->mlx.map[i[1]][(int)prog->info.pos_x] != '1')
			prog->info.pos_y += prog->info.plane_y * prog->info.move_speed;
	}
}

int	key_events(int input, t_program *prog)
{
	if (input == KEYCODE_ESC)
		close_window(prog);
	else if (input == KEYCODE_W)
		vertical_movement(prog, true);
	else if (input == KEYCODE_S)
		vertical_movement(prog, false);
	else if (input == KEYCODE_A)
		horizontal_movement(prog, true);
	else if (input == KEYCODE_D)
		horizontal_movement(prog, false);
	else if (input == KEYCODE_LEFT)
		horizontal_perspective(prog, true);
	else if (input == KEYCODE_RIGHT)
		horizontal_perspective(prog, false);
	update_frame(prog);
	return (0);
}
