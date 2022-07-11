/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:58:49 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/11 19:58:24 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	close_window(t_program *prog)
{
	free_2d_array(prog->mlx.map);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[0].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[1].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[2].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[3].ptr);
	mlx_destroy_image(prog->mlx.ptr, prog->mlx.img[4].ptr);
	mlx_clear_window(prog->mlx.ptr, prog->mlx.window);
	mlx_destroy_window(prog->mlx.ptr, prog->mlx.window);
	exit(0);
}