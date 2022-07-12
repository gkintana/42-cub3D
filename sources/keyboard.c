/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:54:46 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/12 13:56:00 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	w_and_s_keys(t_program *prog, bool move_forward)
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

static void	a_and_d_keys(t_program *prog, bool move_left)
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

/*
** i[0] = stores the value of the player's rotate speed
** i[1] = stores a copy of the player's vector x value before updating
** i[2] = stores a copy of the player's plane x value before updating
** i[3] = boolean which indicates if rotation speed is negative
*/
void	left_and_right_keys(t_program *prog, bool rotate_left)
{
	double	i[4];

	ft_bzero(&i, 4 * sizeof(double));
	i[0] = prog->info.rotate_speed;
	if (rotate_left)
	{
		i[3] = 1;
		i[1] = prog->info.vec_x;
		prog->info.vec_x = calculate_rotation(prog, 1, i);
		prog->info.vec_y = calculate_rotation(prog, 2, i);
		i[2] = prog->info.plane_x;
		prog->info.plane_x = calculate_rotation(prog, 3, i);
		prog->info.plane_y = calculate_rotation(prog, 4, i);
	}
	else
	{
		i[3] = 0;
		i[1] = prog->info.vec_x;
		prog->info.vec_x = calculate_rotation(prog, 1, i);
		prog->info.vec_y = calculate_rotation(prog, 2, i);
		i[2] = prog->info.plane_x;
		prog->info.plane_x = calculate_rotation(prog, 3, i);
		prog->info.plane_y = calculate_rotation(prog, 4, i);
	}
}

int	key_events(int input, t_program *prog)
{
	if (input == KEYCODE_ESC)
		close_window(prog);
	else if (input == KEYCODE_W)
		w_and_s_keys(prog, true);
	else if (input == KEYCODE_A)
		a_and_d_keys(prog, true);
	else if (input == KEYCODE_S)
		w_and_s_keys(prog, false);
	else if (input == KEYCODE_D)
		a_and_d_keys(prog, false);
	else if (input == KEYCODE_LEFT)
		left_and_right_keys(prog, true);
	else if (input == KEYCODE_RIGHT)
		left_and_right_keys(prog, false);

	else if (input == KEYCODE_UP)
	{
		prog->info.pitch += 400 * prog->info.move_speed;
		if (prog->info.pitch > 200)
			prog->info.pitch = 200;
	}
	else if (input == KEYCODE_DOWN)
	{
		prog->info.pitch -= 400 * prog->info.move_speed;
		if (prog->info.pitch < -200)
			prog->info.pitch = -200;
	}
	update_frame(prog);
	return (0);
}