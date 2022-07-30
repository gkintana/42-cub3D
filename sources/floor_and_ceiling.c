/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:50:21 by gkintana          #+#    #+#             */
/*   Updated: 2022/07/30 13:14:31 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	get_floor_rgb(t_program *prog)
{
	char	**rgb_array;
	int		rgb[3];

	rgb_array = ft_split(prog->tex.floor, ',');
	ft_bzero(&rgb, 3 * sizeof(int));
	rgb[0] = ft_atoi(rgb_array[0]);
	rgb[1] = ft_atoi(rgb_array[1]);
	rgb[2] = ft_atoi(rgb_array[2]);
	printf("Floor RGB (Hex Value) = %c%c%c%c%c%c\n", HEX_SYSTEM[rgb[0] / 16],
													HEX_SYSTEM[rgb[0] % 16],
													HEX_SYSTEM[rgb[1] / 16],
													HEX_SYSTEM[rgb[1] % 16],
													HEX_SYSTEM[rgb[2] / 16],
													HEX_SYSTEM[rgb[2] % 16]);
	prog->tex.floor_rgb = (int)(((rgb[0] / 16) * pow(16, 5))
							+ ((rgb[0] % 16) * pow(16, 4))
							+ ((rgb[1] / 16) * pow(16, 3))
							+ ((rgb[1] % 16) * pow(16, 2))
							+ ((rgb[2] / 16) * pow(16, 1))
							+ ((rgb[2] % 16) * pow(16, 0)));
	printf("Floor RGB (Int Value) = %d\n", prog->tex.floor_rgb);
	free_2d_array(rgb_array);
}

void	get_ceiling_rgb(t_program *prog)
{
	char	**rgb_array;
	int		rgb[3];

	rgb_array = ft_split(prog->tex.ceiling, ',');
	ft_bzero(&rgb, 3 * sizeof(int));
	rgb[0] = ft_atoi(rgb_array[0]);
	rgb[1] = ft_atoi(rgb_array[1]);
	rgb[2] = ft_atoi(rgb_array[2]);
	printf("Ceiling RGB (Hex Value) = %c%c%c%c%c%c\n", HEX_SYSTEM[rgb[0] / 16],
													HEX_SYSTEM[rgb[0] % 16],
													HEX_SYSTEM[rgb[1] / 16],
													HEX_SYSTEM[rgb[1] % 16],
													HEX_SYSTEM[rgb[2] / 16],
													HEX_SYSTEM[rgb[2] % 16]);
	prog->tex.ceiling_rgb = (int)(((rgb[0] / 16) * pow(16, 5))
							+ ((rgb[0] % 16) * pow(16, 4))
							+ ((rgb[1] / 16) * pow(16, 3))
							+ ((rgb[1] % 16) * pow(16, 2))
							+ ((rgb[2] / 16) * pow(16, 1))
							+ ((rgb[2] % 16) * pow(16, 0)));
	printf("Ceiling RGB (Int Value) = %d\n", prog->tex.ceiling_rgb);
	free_2d_array(rgb_array);
}