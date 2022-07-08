/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:58:49 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/09 01:59:03 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	close_window(t_data *data)
{
	free_2d_array(data->map);
	mlx_destroy_image(data->mlx, data->img[0].ptr);
	mlx_destroy_image(data->mlx, data->img[1].ptr);
	mlx_clear_window(data->mlx, data->mlx_window);
	mlx_destroy_window(data->mlx, data->mlx_window);
	exit(0);
}