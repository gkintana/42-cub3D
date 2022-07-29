/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:04:39 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/29 13:53:30 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
** calls the mlx_mouse_get_pos function to update the t_mouse structure. Had
** to separate it from mouse_events since it never stopped rotating on linux,
** needs to be tested on mac
*/
static void	update_mouse_coordinates(t_program *prog)
{
	mlx_mouse_get_pos(prog->mlx.ptr, prog->mlx.window, &prog->mouse.new_x,
		&prog->mouse.new_y);
}

/*
** event handler for mouse inputs. Lowers the camera rotation speed before
** calculating and updating the frame for a smoother experience, then sets it
** back to its original value
*/
int	mouse_events(int x, int y, t_program *prog)
{
	int	rotate_speed;

	rotate_speed = prog->info.rotate_speed;
	update_mouse_coordinates(prog);
	if (abs(prog->mouse.new_x - x) / 3 < abs(prog->mouse.new_y - y))
	{
		if (prog->mouse.new_y < y)
			vertical_perspective(prog, true);
		else
			vertical_perspective(prog, false);
	}
	prog->info.rotate_speed = 0.01;
	if (prog->mouse.new_x < x)
		horizontal_perspective(prog, true);
	else
		horizontal_perspective(prog, false);
	update_frame(prog);
	prog->info.rotate_speed = rotate_speed;
	return (0);
}
