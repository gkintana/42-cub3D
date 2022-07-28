/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 22:47:50 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/28 10:03:27 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	calculate_position_and_vector(t_program *prog, int formula)
{
	double	result;

	result = 0;
	if (formula == 1)
		result = prog->info.pos_x + prog->info.vec_x * prog->info.move_speed;
	else if (formula == 2)
		result = prog->info.pos_y + prog->info.vec_y * prog->info.move_speed;
	else if (formula == 3)
		result = prog->info.pos_x - prog->info.vec_x * prog->info.move_speed;
	else if (formula == 4)
		result = prog->info.pos_y - prog->info.vec_y * prog->info.move_speed;
	return (result);
}

double	calculate_position_and_plane(t_program *prog, int formula)
{
	double	result;

	result = 0;
	if (formula == 1)
		result = prog->info.pos_x - prog->info.plane_x * prog->info.move_speed;
	else if (formula == 2)
		result = prog->info.pos_y - prog->info.plane_y * prog->info.move_speed;
	else if (formula == 3)
		result = prog->info.pos_x + prog->info.plane_x * prog->info.move_speed;
	else if (formula == 4)
		result = prog->info.pos_y + prog->info.plane_y * prog->info.move_speed;
	return (result);
}

double	calculate_rotation(t_program *prog, int formula, double i[])
{
	double	j[2];

	ft_bzero(&j, 2 * sizeof(double));
	j[0] = i[0];
	if (i[3])
		j[0] *= -1;
	if (formula == 1)
		j[1] = i[1] * cos(j[0]) - prog->info.vec_y * sin(j[0]);
	else if (formula == 2)
		j[1] = i[1] * sin(j[0]) + prog->info.vec_y * cos(j[0]);
	else if (formula == 3)
		j[1] = i[2] * cos(j[0]) - prog->info.plane_y * sin(j[0]);
	else if (formula == 4)
		j[1] = i[2] * sin(j[0]) + prog->info.plane_y * cos(j[0]);
	return (j[1]);
}
