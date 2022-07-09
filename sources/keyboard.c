/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:54:46 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/10 02:08:09 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	key_events(int input, t_data *data)
{
	if (input == KEYCODE_ESC)
		close_window(data);
	else if (input == KEYCODE_W)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x + data->vec_x * data->move_speed)] == '0')
			data->pos_x += data->vec_x * data->move_speed;
		if (data->map[(int)(data->pos_y + data->vec_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y += data->vec_y * data->move_speed;
	}
	else if (input == KEYCODE_A)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x - data->plane_x * data->move_speed)] == '0')
			data->pos_x -= data->plane_x * data->move_speed;
		if (data->map[(int)(data->pos_y - data->plane_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y -= data->plane_y * data->move_speed;
	}
	else if (input == KEYCODE_S)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x - data->vec_x * data->move_speed)] == '0')
			data->pos_x -= data->vec_x * data->move_speed;
		if (data->map[(int)(data->pos_y - data->vec_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y -= data->vec_y * data->move_speed;
	}
	else if (input == KEYCODE_D)
	{
		if (data->map[(int)data->pos_y][(int)(data->pos_x + data->plane_x * data->move_speed)] == '0')
			data->pos_x += data->plane_x * data->move_speed;
		if (data->map[(int)(data->pos_y + data->plane_y * data->move_speed)][(int)data->pos_x] == '0')
			data->pos_y += data->plane_y * data->move_speed;
	}
	else if (input == KEYCODE_LEFT)
	{
		double	old_vec_x = data->vec_x;
		data->vec_x = data->vec_x * cos(-data->rotate_speed) - data->vec_y * sin(-data->rotate_speed);
		data->vec_y = old_vec_x * sin(-data->rotate_speed) + data->vec_y * cos(-data->rotate_speed);
		double	old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(-data->rotate_speed) - data->plane_y * sin(-data->rotate_speed);
		data->plane_y = old_plane_x * sin(-data->rotate_speed) + data->plane_y * cos(-data->rotate_speed);
	}
	else if (input == KEYCODE_RIGHT)
	{
		double	old_vec_x = data->vec_x;
		data->vec_x = data->vec_x * cos(data->rotate_speed) - data->vec_y * sin(data->rotate_speed);
		data->vec_y = old_vec_x * sin(data->rotate_speed) + data->vec_y * cos(data->rotate_speed);
		double	old_plane_x = data->plane_x;
		data->plane_x = data->plane_x * cos(data->rotate_speed) - data->plane_y * sin(data->rotate_speed);
		data->plane_y = old_plane_x * sin(data->rotate_speed) + data->plane_y * cos(data->rotate_speed);
	}
	mlx_destroy_image(data->mlx, data->img[0].ptr);
	data->img[0].ptr = mlx_new_image(data->mlx, data->win_width, data->win_height);
	data->img[0].addr = mlx_get_data_addr(data->img[0].ptr, &data->img[0].bpp, &data->img[0].len, &data->img[0].endian);
	mlx_clear_window(data->mlx, data->mlx_window);
	raycast_loop(data);
	return (0);
}