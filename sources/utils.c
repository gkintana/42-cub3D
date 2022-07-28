/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 02:02:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/28 10:03:13 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*
 * this is the my_mlx_pixel_put function from the minilibx documentation
 */
void	put_pixel_at_addr(t_image *img, int x, int y, int color)
{
	char			*pixel;
	unsigned int	pixel_position;

	pixel_position = (y * img->len) + (x * (img->bpp >> 3));
	pixel = img->addr + pixel_position;
	*(unsigned int *)pixel = color;
}

void	free_2d_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
